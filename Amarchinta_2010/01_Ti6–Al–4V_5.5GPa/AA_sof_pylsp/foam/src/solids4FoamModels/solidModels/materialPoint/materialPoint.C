#include "materialPoint.H"
#include "fvm.H"
#include "fvc.H"
#include "fvMatrices.H"
#include "addToRunTimeSelectionTable.H"

namespace Foam{ namespace solidModels {

defineTypeNameAndDebug(materialPoint, 0);
//addToRunTimeSelectionTable(physicsModel, materialPoint, solid);
addToRunTimeSelectionTable(solidModel, materialPoint, dictionary);

materialPoint::materialPoint(Time& runTime, const word& region) :
    solidModel(typeName, runTime, region),
    strainXXseries_(solidModelDict()),
    osStrainStressData(runTime.path() + "/strainStress"),
    osEpsP(runTime.path() + "/epsP") {
}

bool materialPoint::evolve() {
    Info<< "Evolving solid solver" << endl;


    scalar curStrainXX(strainXXseries_(runTime().value()));
    gradD()[0].xx() = curStrainXX;

    scalar max = 0;
    scalar min = 0;
    scalar deltaStrainXX = 0;
    
    while (true) {
        scalar x = 0.5 * (min + max);
        gradD()[0].yy() = gradD()[0].zz() = x * (curStrainXX + deltaStrainXX);
        mechanical().correct(sigma());
        scalar f(sigma()[0].yy());

        if (fabs(f) < fabs(1e-9 * sigma()[0].xx())) {
            break;
        }

        if (fabs(min - max) < SMALL) {
            deltaStrainXX += 0.1;
            max = 0.5;
            min = -0.5;
        }
        
        if (f > 0.0) {
            max = x;
        } else {
            min = x;
        }
    }


    symmTensor strain(symm(gradD()[0]));
    symmTensor stress(sigma()[0]);
    

    scalar strainEq(Foam::sqrt((2.0 / 3.0) * magSqr(dev(strain))));
    scalar stressEq(Foam::sqrt((3.0 / 2.0) * magSqr(dev(stress))));

    if (strain.xx() - strain.yy() < 0.0) {
        strainEq *= -1.0;
    }

    if (stress.xx() < 0.0) {
        stressEq *= -1.0;
    }


    osStrainStressData << strainEq << "," << stressEq << endl;
    return true;
}

tmp<vectorField> materialPoint::tractionBoundarySnGrad(const vectorField& traction, const scalarField& pressure, const fvPatch& patch) const {
    return tmp<vectorField>(new vectorField((traction * 0)));
}

}}
