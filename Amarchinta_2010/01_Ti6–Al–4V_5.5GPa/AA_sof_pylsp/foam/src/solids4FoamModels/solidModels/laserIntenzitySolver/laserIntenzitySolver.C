#include <iostream>
#include <vector>
#include <iterator>

#include "laserIntenzitySolver.H"
#include "fvm.H"
#include "fvc.H"
#include "fvMatrices.H"
#include "addToRunTimeSelectionTable.H"
#include "../fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.H"

namespace Foam{ namespace solidModels {

defineTypeNameAndDebug(laserIntenzitySolver, 0);
//addToRunTimeSelectionTable(physicsModel, laserIntenzitySolver, solid);
addToRunTimeSelectionTable(solidModel, laserIntenzitySolver, dictionary);

laserIntenzitySolver::laserIntenzitySolver(Time& runTime, const word& region) :
    solidModel(typeName, runTime, region),
    p_(IOobject("p", runTime.timeName(), mesh(), IOobject::READ_IF_PRESENT, IOobject::AUTO_WRITE), mesh(), dimensionedScalar("zero", dimPressure, 0), "calculated"),
    pMAX_(IOobject("pMAX", runTime.timeName(), mesh(), IOobject::READ_IF_PRESENT, IOobject::AUTO_WRITE), mesh(), dimensionedScalar("zero", dimPressure, 0), "calculated"),
    pSUM_(IOobject("pSUM", runTime.timeName(), mesh(), IOobject::READ_IF_PRESENT, IOobject::AUTO_WRITE), mesh(), dimensionedScalar("zero", dimPressure, 0), "calculated") {
    pMAX_.oldTime();
    pSUM_.oldTime();

    std::vector<word> writeFields = {};
    forAll(mesh().thisDb().names(), i) {
        bool bWrite = false;
        for(word field : writeFields) {
            if (field == mesh().thisDb().names()[i]) {
                bWrite = true;
                continue;
            }
        }
        regIOobject& obj = const_cast<regIOobject&>(mesh().thisDb().lookupObject<regIOobject>(mesh().thisDb().names()[i]));
        if (bWrite) {
            obj.writeOpt() = IOobject::AUTO_WRITE;
        } else {
            obj.writeOpt() = IOobject::NO_WRITE;
        }
    }
}

bool laserIntenzitySolver::evolve() {
    Info<< "Evolving solid solver" << endl;

    do {
        D().correctBoundaryConditions();
        forAll(D().boundaryField(), patchI) {
            if (isA<laserProcessingPressureFvPatchVectorField>(D().boundaryField()[patchI])) {
                const laserProcessingPressureFvPatchVectorField solidTraction = refCast<const laserProcessingPressureFvPatchVectorField>(D().boundaryField()[patchI]);
                p_.boundaryFieldRef()[patchI] = solidTraction.pressure();
                pMAX_.boundaryFieldRef()[patchI] = max(solidTraction.pressure(), pMAX_.oldTime().boundaryField()[patchI]);
                pSUM_.boundaryFieldRef()[patchI] = solidTraction.pressure() + pSUM_.oldTime().boundaryField()[patchI];
            }
        }
    }
    while (mesh().update());   
    return true;
}

tmp<vectorField> laserIntenzitySolver::tractionBoundarySnGrad(const vectorField& traction, const scalarField& pressure, const fvPatch& patch) const {
    return tmp<vectorField>((traction));
}

}}
