#include "myExplicitLinGeomTotalDispSolid.H"
#include "fvm.H"
#include "fvc.H"
#include "fvMatrices.H"
#include "addToRunTimeSelectionTable.H"

//~ #include "yieldedAvailable.H"                                       // see VAR B in the ::end() method below

namespace Foam{ 
    namespace solidModels 
    {
        // Static data members ************************************ //
        defineTypeNameAndDebug(myExplicitLinGeomTotalDispSolid, 0);
        //addToRunTimeSelectionTable(physicsModel, myExplicitLinGeomTotalDispSolid, solid);
        addToRunTimeSelectionTable(solidModel, myExplicitLinGeomTotalDispSolid, dictionary);
        
        // Private member functions ******************************* //
        void myExplicitLinGeomTotalDispSolid::updateStress()
        {
            DD() = D() - D().oldTime();
            mechanical().grad(D(), gradD());
            gradDD() = gradD() - gradD().oldTime();
            mechanical().correct(sigma());
        }
        
        // Constructors *************************************** //
        myExplicitLinGeomTotalDispSolid::myExplicitLinGeomTotalDispSolid
        (
            Time& runTime, 
            const word& region
        ):
        solidModel(typeName, runTime, region),
        bUpdateDeltaT(true),
        impK_(mechanical().impK()),
        impKf_(mechanical().impKf()),
        JSTScaleFactor_(solidModelDict().lookupOrDefault<scalar>("JSTScaleFactor", 0.01)), 
        waveSpeed_(IOobject("waveSpeed", runTime.timeName(), mesh(), IOobject::NO_READ, IOobject::NO_WRITE), fvc::interpolate(Foam::sqrt(impK_ / rho()))),
        energies_(mesh(), solidModelDict()),
        a_(IOobject("a", runTime.timeName(), mesh(), IOobject::READ_IF_PRESENT, IOobject::AUTO_WRITE), mesh(), dimensionedVector("zero", dimVelocity / dimTime, vector::zero), "zeroGradient"),
        F0_(IOobject("F0", runTime.timeName(), mesh(), IOobject::READ_IF_PRESENT, IOobject::AUTO_WRITE), mesh(), dimensionedVector("zero", dimForce / dimVolume, vector::zero), "zeroGradient") 
        {
            a_.oldTime();
            U().oldTime();
        
            setDeltaT(runTime);
            bUpdateDeltaT = true;
            
            for (int i = 1; i<100; i++) {
                D().correctBoundaryConditions();
                updateStress();
            }
            
        
            F0_.internalFieldRef() = (fvc::div((mesh().Sf() & fvc::interpolate(sigma())))().internalField());
        
            // a_.internalField() = F0_ / rho().internalField() + g().value();
            // a_.correctBoundaryConditions();
        }
        
        void myExplicitLinGeomTotalDispSolid::setDeltaT(Time& runTime) 
        {
            if (!bUpdateDeltaT) return;
        
            const scalar requiredDeltaT(
                1.0 / gMax(Field<scalar>(mesh().surfaceInterpolation::deltaCoeffs().internalField() * waveSpeed_.internalField()))
            );
            const scalar maxCo = runTime.controlDict().lookupOrDefault<scalar>("maxCo", 0.7071);
            scalar newDeltaT = maxCo * requiredDeltaT;
            //if (runTime.value() < 20.0e-09)                                     // Note (MI): here, I hardcoded approximate laser pulse duration
            if (std::fmod(runTime.value(), 1) < 20.0e-09)                         // Note (AK): "remainder after division by 1" -- the same but works for other shots than only the first one
            {    
                newDeltaT *= 0.05;                                              //increase time resolution at the simulation start
                Info << "Note: decreased deltaT to improve temporal integration at the simulation start" << endl;
                Info << "trueCo = " << newDeltaT/requiredDeltaT << endl;
            }
            else
            {
                bUpdateDeltaT = false;                                          //keep constant time step only after this part of simulation
            }
            Info << "maxCo = " << maxCo << nl << "deltaT = " << newDeltaT << nl << endl;
            Info << "current time = " << runTime.value() << endl;
            runTime.setDeltaT(newDeltaT);
            
        }
    
        bool myExplicitLinGeomTotalDispSolid::evolve() 
        {
            Info<< "Evolving solid solver" << endl;
        
            do {
                Info<< "Solving the momentum equation for D" << endl;
                
                const dimensionedScalar& deltaT = time().deltaT();
                const dimensionedScalar& deltaT0 = time().deltaT0();
                
                U() = U().oldTime() + 0.5 * (deltaT + deltaT0) * a_.oldTime();
                D() = D().oldTime() + deltaT * U();
                D().correctBoundaryConditions();
                updateStress();
                
                a_.internalFieldRef() = (
                    fvc::div((mesh().Sf() & fvc::interpolate(sigma())))().internalField() 
                    - F0_.internalField()
                    //solids4foam guy: "Actually Rhie-Chow
                    
                    + JSTScaleFactor_*(
                        fvc::laplacian(impKf_, D(), "laplacian(DD,D)")
                      - fvc::div(impKf_*mesh().Sf() & fvc::interpolate(gradD()))
                      )().internalField()
                    
                    //solids4foam had this uncommented:
                    /*
                    - JSTScaleFactor_*fvc::laplacian
                    (
                        mesh().magSf(),
                        fvc::laplacian
                        (
                            0.5*(deltaT + deltaT0)*impKf_, U(), "laplacian(DU,U)"
                        ),
                        "laplacian(DU,U)"
                    )().internalField()
                    */
                    //solids4foam: Lax-Friedrichs smoothing
                    /*
                    + JSTScaleFactor_*fvc::laplacian
                    (
                        0.5*(deltaT + deltaT0)*impKf_,
                        U(),
                        "laplacian(DU,U)"               
                    )().internalField() 
                    */
                ) / rho().internalField();
                // + g().value();
                a_.correctBoundaryConditions();
                energies_.checkEnergies(rho(), U(), D(), DD(), sigma(), gradD(), gradDD(), waveSpeed_, g(), 0.0, impKf_);
            }
            while (mesh().update());
            return true;
        }
        
        void myExplicitLinGeomTotalDispSolid::end() 
        {
            Info << "Additional smoothing of the epsilonP field (only the cells yielding during the simulation are updated)" << endl;
            
            // MI: VARIANT A - there is a problem with the fact that
            //     yielded has been created by myLinearElasticMisesPlastic
            //     as a result, it is not directly available in mesh()
            //     -> the code compiles but always ends with yielded not found
            
            
            //~ if (mesh().foundObject<volSymmTensorField>("epsilonP") and mesh().foundObject<volScalarField>("yielded"))
            //~ {
                //~ volSymmTensorField& epsilonP = const_cast<volSymmTensorField&>//lookup
                //~ (
                    //~ mesh().lookupObject<volSymmTensorField>("epsilonP")
                //~ );
                //~ volSymmTensorField epsilonPSmoothed(epsilonP);          //copy
                
                //~ volScalarField& yielded = const_cast<volScalarField&>//lookup
                //~ (
                    //~ mesh().lookupObject<volScalarField>("yielded")
                //~ );
                
                //~ for (label pass=0; pass<=1; pass++)                     //at the moment, run only single smoothing iteration
                //~ {
                    //~ epsilonPSmoothed = fvc::average(fvc::interpolate(epsilonPSmoothed));
                    //~ epsilonPSmoothed.correctBoundaryConditions();
                //~ }
//~ #ifdef OPENFOAMESIORFOUNDATION
                //~ forAll(epsilonP.primitiveField(), celli)
                //~ {
                    //~ if (yielded.primitiveField()[celli] > SMALL)
                    //~ {
                        //~ epsilonP.primitiveFieldRef()[celli] = epsilonPSmoothed.primitiveFieldRef()[celli];
                    //~ }
                //~ }
//~ #else
                //~ forAll(epsilonP.internalField(), celli)
                //~ {
                    //~ if (yielded.internalField()[celli] > SMALL)
                    //~ {
                        //~ epsilonP.internalField()[celli] = epsilonPSmoothed.internalField()[celli];
                    //~ }
                //~ }
//~ #endif
                //~ epsilonP.write();
            //~ }
            //~ else
            //~ {
                //~ if (mesh().foundObject<volSymmTensorField>("epsilonP"))
                //~ {
                    //~ Info << "No yielded flag is available; ";
                //~ }
                //~ else
                //~ {
                    //~ Info << "No epsilonP is available; ";
                //~ }
                //~ Info << "smoothing of epsilonP not performed" << endl;
            //~ }
            
            
            // MI: VARIANT B - I tried to add virtual method to myLinearElasticMisesPlastic
            //     that would return yielded in a manner similar to 
            //     "impK_(mechanical().impK())"
            //      BUT not all models have yielded() available, so I tried
            //      to prepare the code to return yielded only when defined
            //      and I failed to do so in time
            //      -> the code will not compile
            
            
            //~ if (mesh().foundObject<volSymmTensorField>("epsilonP"))
            //~ {
                //~ if (const Foam::yieldedAvailable* plastic = dynamic_cast<const Foam::yieldedAvailable*>(&mechanical))
                //~ {
                    //~ volSymmTensorField& epsilonP = const_cast<volSymmTensorField&>//lookup
                    //~ (
                        //~ mesh().lookupObject<volSymmTensorField>("epsilonP")
                    //~ );
                    //~ volSymmTensorField epsilonPSmoothed(epsilonP);          //copy
                    
                    //~ const volScalarField& yielded(mechanical().yielded())
                    
                    //~ for (label pass=0; pass<=1; pass++)                     //at the moment, run only single smoothing iteration
                    //~ {
                        //~ epsilonPSmoothed = fvc::average(fvc::interpolate(epsilonPSmoothed));
                        //~ epsilonPSmoothed.correctBoundaryConditions();
                    //~ }
//~ #ifdef OPENFOAMESIORFOUNDATION
                    //~ forAll(epsilonP.primitiveField(), celli)
                    //~ {
                        //~ if (yielded.primitiveField()[celli] > SMALL)
                        //~ {
                            //~ epsilonP.primitiveFieldRef()[celli] = epsilonPSmoothed.primitiveFieldRef()[celli];
                        //~ }
                    //~ }
//~ #else
                    //~ forAll(epsilonP.internalField(), celli)
                    //~ {
                        //~ if (yielded.internalField()[celli] > SMALL)
                        //~ {
                            //~ epsilonP.internalField()[celli] = epsilonPSmoothed.internalField()[celli];
                        //~ }
                    //~ }
//~ #endif
                    //~ epsilonP.write();
                //~ }
            //~ }
            //~ else
            //~ {
                //~ if (mesh().foundObject<volSymmTensorField>("epsilonP"))
                //~ {
                    //~ Info << "No yielded flag is available; ";
                //~ }
                //~ else
                //~ {
                    //~ Info << "No epsilonP is available; ";
                //~ }
                //~ Info << "smoothing of epsilonP not performed" << endl;
            //~ }
            
        }
        
        tmp<vectorField> myExplicitLinGeomTotalDispSolid::tractionBoundarySnGrad
        (
            const vectorField& traction, 
            const scalarField& pressure, 
            const fvPatch& patch
        ) const 
        {
            const label patchID = patch.index();
            const scalarField& impK = impK_.boundaryField()[patchID];
            const tensorField& pGradD = gradD().boundaryField()[patchID];
            const symmTensorField& pSigma = sigma().boundaryField()[patchID];
            const vectorField n(patch.nf());
            return tmp<vectorField>(new vectorField(((traction - n * pressure) - (n & (pSigma - impK * pGradD))) / impK));
        }
    
    }
}
