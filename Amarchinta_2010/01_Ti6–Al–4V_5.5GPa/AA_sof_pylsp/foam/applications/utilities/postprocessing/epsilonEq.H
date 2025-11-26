#ifndef EPSILON_EQ_H
#define EPSILON_EQ_H

#include "postprocessing.H"

struct EpsilonEq : public CalcField {  

    EpsilonEq() : CalcField("epsilonEq", List<word>(1, {"epsilon"})) {}

    void calculate(const Time& runTime, const fvMesh& mesh) {
        volSymmTensorField epsilon(IOobject("epsilon", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::NO_WRITE), mesh);
        volScalarField epsilonEq(IOobject("post_epsilonEq", runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, 0.0);

        forAll(epsilonEq, i) {
            const symmTensor& strain = epsilon[i];
            epsilonEq[i] = Foam::sqrt((2.0 / 3.0) * magSqr(dev(strain)));
        }

        forAll(mesh.boundaryMesh(), patchI) {
            forAll(mesh.boundary()[patchI], patchFaceI) {
                const symmTensor& strain = epsilon.boundaryField()[patchI][patchFaceI];
                epsilonEq.boundaryFieldRef()[patchI][patchFaceI] = Foam::sqrt((2.0 / 3.0) * magSqr(dev(strain)));
            }
        }

        epsilonEq.write();
    }

};

#endif