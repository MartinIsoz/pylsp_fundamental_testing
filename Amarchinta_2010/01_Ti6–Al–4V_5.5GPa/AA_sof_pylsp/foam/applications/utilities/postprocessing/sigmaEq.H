#ifndef SIGMA_EQ_H
#define SIGMA_EQ_H

#include "postprocessing.H"

struct SigmaEq : public CalcField {

    SigmaEq() : CalcField("sigmaEq", List<word>(1, {"sigma"})) {}

    void calculate(const Time& runTime, const fvMesh& mesh) {
        volSymmTensorField sigma(IOobject("sigma", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::NO_WRITE), mesh);
        volScalarField sigmaEq(IOobject("post_sigmaEq", runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, 0.0);

        forAll(sigmaEq, i) {
            const symmTensor& stress = sigma[i];          
            sigmaEq[i] = Foam::sqrt((3.0 / 2.0) * magSqr(dev(stress)));
        }

        forAll(mesh.boundaryMesh(), patchI) {
            forAll(mesh.boundary()[patchI], patchFaceI) {
                const symmTensor& stress = sigma.boundaryField()[patchI][patchFaceI];
                sigmaEq.boundaryFieldRef()[patchI][patchFaceI] = Foam::sqrt((3.0 / 2.0) * magSqr(dev(stress)));
            }
        }

        sigmaEq.write();
    }

};

#endif