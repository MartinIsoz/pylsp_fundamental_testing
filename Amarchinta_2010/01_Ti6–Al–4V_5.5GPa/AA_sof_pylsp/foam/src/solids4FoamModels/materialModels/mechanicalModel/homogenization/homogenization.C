// OpenFOAM
#include "addToRunTimeSelectionTable.H"
#include "fvc.H"
#include "fvm.H"


// OOFEM
#include "oofemlib/oofemtxtdatareader.h"
#include "oofemlib/datastream.h"
#include "oofemlib/util.h"
#include "oofemlib/error.h"
#include "oofemlib/logger.h"
#include "oofemlib/contextioerr.h"
#include "oofemlib/oofem_terminate.h"
#include "sm/EngineeringModels/homogenization.h"
#include "homogenization.H"


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(homogenization, 0);
    addToRunTimeSelectionTable
    (
        mechanicalLaw, homogenization, linGeomMechLaw
    );
}


// * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * * //
void Foam::homogenization::initOOFEM(const dictionary& dict) {
    oofem::oofem_logger.setLogLevel(0);
    string oofem_input_file = dict.lookup("oofem_in");

    dim = readInt(dict.lookup("dim"));


    int noProblems = 0;
    forAll(epsilon_, i) {
        noProblems++;
    }

    forAll(mesh().boundaryMesh(), patchI) {
        forAll(mesh().boundary()[patchI], patchFaceI) {
            noProblems++;
        }
    }

    oofem_problems.resize(noProblems);
    oofem::OOFEMTXTDataReader oofem_dr(oofem_input_file);

    int j = 0;
    forAll(epsilon_, i) {
        oofem::OOFEMTXTDataReader dr(oofem_dr);
        std::unique_ptr<oofem::EngngModel>prob(InstanciateProblem(dr, oofem::_processor, false, NULL, false));
        oofem_problems[j] = std::move(prob);
        dr.finish();
        j++;

        Pout << j << "/" << noProblems << endl;
    }

    Info << "SSSSSSSSSSSSSSS1" << endl;

    forAll(mesh().boundaryMesh(), patchI) {
        forAll(mesh().boundary()[patchI], patchFaceI) {
            oofem::OOFEMTXTDataReader dr(oofem_dr);
            std::unique_ptr<oofem::EngngModel>prob(InstanciateProblem(dr, oofem::_processor, false, NULL, false));
            oofem_problems[j] = std::move(prob);
            dr.finish();
            j++;
        }
    }

    oofem_dr.finish();

     
    forAll(epsilon_, i) {
        if (!oofem_problems[i]) {
            //oofem::OOFEM_LOG_ERROR("Couldn't instanciate OOFEM problem, exiting");
            std::exit(EXIT_FAILURE);
        }


        oofem_problems[i]->checkProblemConsistency();

        oofem_problems[i]->init();
    }

    macroStrain.resize(6);
    macroStress.resize(6);
    macroPlasticStrain.resize(6);
}

void Foam::homogenization::macroLaw2d(oofem::Homogenization* oofem_problem, const symmTensor& strain, symmTensor& stress, symmTensor& plasticStrain) {
    macroStrain.resize(4);
    macroStrain[0] = strain.xx();
    macroStrain[1] = strain.yy();
    macroStrain[2] = 0.0; //strain.zz();
    macroStrain[3] = 2.0 * strain.xy();

    oofem_problem->solveYourself(macroStrain, macroStress, macroPlasticStrain);
    //Pout << oofem_problem->giveMetaStep(1)->giveNumberOfSteps() << endl;
    oofem_problem->giveMetaStep(1)->setNumberOfSteps(oofem_problem->giveMetaStep(1)->giveNumberOfSteps() + 1);  

    stress.xx() = -macroStress[0];
    stress.yy() = -macroStress[1];
    stress.zz() = -macroStress[2];
    stress.yz() = 0.0;
    stress.xz() = 0.0;
    stress.xy() = -macroStress[3];

    plasticStrain.xx() = -macroPlasticStrain[0];
    plasticStrain.yy() = -macroPlasticStrain[1];
    plasticStrain.zz() = -macroPlasticStrain[2];
    plasticStrain.yz() = 0.0;
    plasticStrain.xz() = 0.0;
    plasticStrain.xy() = -0.5 * macroPlasticStrain[3];
}

void Foam::homogenization::macroLaw3d(oofem::Homogenization* oofem_problem, const symmTensor& strain, symmTensor& stress, symmTensor& plasticStrain) {
    macroStrain.resize(6);
    macroStrain[0] = strain.xx();
    macroStrain[1] = strain.yy();
    macroStrain[2] = strain.zz();
    macroStrain[3] = 2.0 * strain.yz();
    macroStrain[4] = 2.0 * strain.xz();
    macroStrain[5] = 2.0 * strain.xy();


    oofem_problem->solveYourself(macroStrain, macroStress, macroPlasticStrain);
    //Pout << oofem_problem->giveMetaStep(1)->giveNumberOfSteps() << endl;
    oofem_problem->giveMetaStep(1)->setNumberOfSteps(oofem_problem->giveMetaStep(1)->giveNumberOfSteps() + 1);

    stress.xx() = -macroStress[0];
    stress.yy() = -macroStress[1];
    stress.zz() = -macroStress[2];
    stress.yz() = -macroStress[3];
    stress.xz() = -macroStress[4];
    stress.xy() = -macroStress[5];

    plasticStrain.xx() = -macroPlasticStrain[0];
    plasticStrain.yy() = -macroPlasticStrain[1];
    plasticStrain.zz() = -macroPlasticStrain[2];
    plasticStrain.yz() = -0.5 * macroPlasticStrain[3];
    plasticStrain.xz() = -0.5 * macroPlasticStrain[4];
    plasticStrain.xy() = -0.5 * macroPlasticStrain[5];
}


// Construct from dictionary
Foam::homogenization::homogenization
(
    const word& name,
    const fvMesh& mesh,
    const dictionary& dict,
    const nonLinearGeometry::nonLinearType& nonLinGeom
)
:
    mechanicalLaw(name, mesh, dict, nonLinGeom),
    rho_(dict.lookup("rho")),
    mu_("mu", dimPressure, 0.0),
    K_("K", dimPressure, 0.0),
    E_("E", dimPressure, 0.0),
    nu_("nu", dimless, 0.0),
    lambda_("lambda", dimPressure, 0.0),
    epsilon_(IOobject("epsilon", mesh.time().timeName(), mesh, IOobject::READ_IF_PRESENT, IOobject::AUTO_WRITE), mesh, dimensionedSymmTensor("zero", dimless, symmTensor::zero)),
    epsilonP_(IOobject("epsilonP", mesh.time().timeName(), mesh, IOobject::NO_READ, IOobject::AUTO_WRITE), mesh, dimensionedSymmTensor("zero", dimless, symmTensor::zero))
{
    initOOFEM(dict);

    // Force storage of strain old time
    epsilon_.oldTime();

    // Read elastic parameters
    // The user can specify E and nu or mu and K
    if (dict.found("E") && dict.found("nu"))
    {
        // Read the Young's modulus
        E_ = dimensionedScalar(dict.lookup("E"));

        // Read the Poisson's ratio
        nu_ = dimensionedScalar(dict.lookup("nu"));

        // Set the shear modulus
        mu_ = E_/(2.0*(1.0 + nu_));

        // Set the bulk modulus
        if (nu_.value() < 0.5)
        {
            K_ = (nu_*E_/((1.0 + nu_)*(1.0 - 2.0*nu_))) + (2.0/3.0)*mu_;
        }
        else
        {
            K_.value() = GREAT;
        }
    }
    else if (dict.found("mu") && dict.found("K"))
    {
        // Read shear modulus
        mu_ = dimensionedScalar(dict.lookup("mu"));

        // Read bulk modulus
        K_ = dimensionedScalar(dict.lookup("K"));

        // Calculate Young's modulus
        E_ = 9.0*K_*mu_/(3.0*K_ + mu_);

        // Calculate Poisson's ratio
        nu_ = (3.0*K_ - 2.0*mu_)/(2.0*(3.0*K_ + mu_));
    }
    else
    {
        FatalErrorIn
        (
            "homogenizationMisesPlastic::homogenizationMisesPlastic::()"
        )   << "Either E and nu or mu and K elastic parameters should be "
            << "specified" << abort(FatalError);
    }

    // Set first Lame parameter
    if (nu_.value() < 0.5)
    {
        lambda_ = nu_*E_/((1.0 + nu_)*(1.0 - 2.0*nu_));
    }
    else
    {
        lambda_.value() = GREAT;
    }

    // Check for physical Poisson's ratio
    if (nu_.value() < -1.0 || nu_.value() > 0.5)
    {
        FatalErrorIn
        (
            "Foam::homogenization::homogenization\n"
            "(\n"
            "    const word& name,\n"
            "    const fvMesh& mesh,\n"
            "    const dictionary& dict\n"
            ")"
        )   << "Unphysical Poisson's ratio: nu should be >= -1.0 and <= 0.5"
            << abort(FatalError);
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::homogenization::~homogenization() {
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField> Foam::homogenization::rho() const
{
    tmp<volScalarField> tresult
    (
        new volScalarField
        (
            IOobject
            (
                "rho",
                mesh().time().timeName(),
                mesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh(),
            rho_,
            zeroGradientFvPatchScalarField::typeName
        )
    );

#ifdef OPENFOAMESIORFOUNDATION
    tresult.ref().correctBoundaryConditions();
#else
    tresult().correctBoundaryConditions();
#endif

    return tresult;
}


Foam::tmp<Foam::volScalarField> Foam::homogenization::impK() const
{
    if (nu_.value() == 0.5)
    {
        return tmp<volScalarField>
        (
            new volScalarField
            (
                IOobject
                (
                    "impK",
                    mesh().time().timeName(),
                    mesh(),
                    IOobject::NO_READ,
                    IOobject::NO_WRITE
                ),
                mesh(),
                2.0*mu_
            )
        );
    }
    else
    {
        return tmp<volScalarField>
        (
            new volScalarField
            (
                IOobject
                (
                    "impK",
                    mesh().time().timeName(),
                    mesh(),
                    IOobject::NO_READ,
                    IOobject::NO_WRITE
                ),
                mesh(),
                2.0*mu_ + lambda_
            )
        );
    }

}


const Foam::dimensionedScalar& Foam::homogenization::mu() const
{
    return mu_;
}


const Foam::dimensionedScalar& Foam::homogenization::K() const
{
    return K_;
}


const Foam::dimensionedScalar& Foam::homogenization::E() const
{
    return E_;
}


const Foam::dimensionedScalar& Foam::homogenization::nu() const
{
    return nu_;
}


const Foam::dimensionedScalar& Foam::homogenization::lambda() const
{
    return lambda_;
}


void Foam::homogenization::correct(volSymmTensorField& sigma)
{   
    if (incremental()) {
        FatalErrorIn
        (
            "void Foam::homogenization::"
            "correct(volSymmTensorField& sigma)"
        )   << "For incremental "
            << "not implemented!" << abort(FatalError);
    } else {
        const volTensorField& gradD = mesh().lookupObject<volTensorField>("grad(D)");
        epsilon_ = symm(gradD);
    }

    int j = 0;
    forAll(epsilon_, i) {
        oofem::Homogenization* oofem_homo_problem = dynamic_cast<oofem::Homogenization*>(oofem_problems[j]->giveEngngModel());
        if (dim == 2) {
            macroLaw2d(oofem_homo_problem, epsilon_[i], sigma[i], epsilonP_[i]);
        } else if (dim == 3) {
            macroLaw3d(oofem_homo_problem, epsilon_[i], sigma[i], epsilonP_[i]);
        }

        
        j++;
    }

    forAll(mesh().boundaryMesh(), patchI) {
        forAll(mesh().boundary()[patchI], patchFaceI) {
            oofem::Homogenization* oofem_homo_problem = dynamic_cast<oofem::Homogenization*>(oofem_problems[j]->giveEngngModel());
            if (dim == 2) {
                macroLaw2d(oofem_homo_problem, epsilon_.boundaryField()[patchI][patchFaceI], sigma.boundaryField()[patchI][patchFaceI], epsilonP_.boundaryField()[patchI][patchFaceI]);
            } else if (dim == 3) {
                macroLaw3d(oofem_homo_problem, epsilon_.boundaryField()[patchI][patchFaceI], sigma.boundaryField()[patchI][patchFaceI], epsilonP_.boundaryField()[patchI][patchFaceI]);
            }
            j++;
        }
    }
}


void Foam::homogenization::correct(surfaceSymmTensorField& sigma)
{
    FatalErrorIn
    (
        "void Foam::homogenization::"
        "correct(surfaceSymmTensorField& sigma)"
    )   << "Not Implemented" << abort(FatalError);
}


// ************************************************************************* //