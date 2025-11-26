#ifndef EPSILONP_EQ_H
#define EPSILONP_EQ_H

#include "postprocessing.H"

struct EpsilonPEq : public CalcField {

    EpsilonPEq() : CalcField("epsilonPEq", List<word>(1, {"epsilonP"})) {}

    void calculate(const Time& runTime, const fvMesh& mesh) {
        volSymmTensorField epsilonP(IOobject("epsilonP", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::NO_WRITE), mesh);
        volScalarField epsilonPEq(IOobject("post_epsilonPEq", runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, 0.0);

        forAll(epsilonPEq, i) {
            const symmTensor& strainP = epsilonP[i];          
            epsilonPEq[i] = Foam::sqrt((2.0 / 3.0) * magSqr(dev(strainP)));
        }

        forAll(mesh.boundaryMesh(), patchI) {
            forAll(mesh.boundary()[patchI], patchFaceI) {
                const symmTensor& strainP = epsilonP.boundaryField()[patchI][patchFaceI];
                epsilonPEq.boundaryFieldRef()[patchI][patchFaceI] = Foam::sqrt((2.0 / 3.0) * magSqr(dev(strainP)));
            }
        }

        epsilonPEq.write();
    }

};

#endif