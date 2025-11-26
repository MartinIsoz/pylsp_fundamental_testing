#ifndef PSTRESS_H
#define PSTRESS_H

#include "postprocessing.H"

struct PrincipalStress : public CalcField {
    vector m_eigValues;
    tensor m_eigVectors;
    vector m_eigVector_1;
    vector m_eigVector_2;
    vector m_eigVector_3;

    PrincipalStress() : CalcField("pstress", List<word>(1, {"sigma"})) {}

    void sort() {
        m_eigVector_1.x() = m_eigVectors.xx();
        m_eigVector_1.y() = m_eigVectors.xy();
        m_eigVector_1.z() = m_eigVectors.xz();

        m_eigVector_2.x() = m_eigVectors.yx();
        m_eigVector_2.y() = m_eigVectors.yy();
        m_eigVector_2.z() = m_eigVectors.yz();

        m_eigVector_3.x() = m_eigVectors.zx();
        m_eigVector_3.y() = m_eigVectors.zy();
        m_eigVector_3.z() = m_eigVectors.zz();

        if (m_eigValues[0] > m_eigValues[1]) {
            std::swap(m_eigValues[0], m_eigValues[1]);
            std::swap(m_eigVector_1, m_eigVector_2);
        }
        if (m_eigValues[1] > m_eigValues[2]) {
            std::swap(m_eigValues[1], m_eigValues[2]);
            std::swap(m_eigVector_2, m_eigVector_3);
        }
        if (m_eigValues[0] > m_eigValues[1]) {
            std::swap(m_eigValues[0], m_eigValues[1]);
            std::swap(m_eigVector_1, m_eigVector_2);
        }
    }


    void calculate(const Time& runTime, const fvMesh& mesh) {
        volSymmTensorField sigma(IOobject("sigma", runTime.timeName(), mesh, IOobject::MUST_READ, IOobject::NO_WRITE), mesh);
        volVectorField pstress(IOobject("post_pstress", runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, vector::zero);
        volVectorField pstress_v1(IOobject("post_pstress_v1", runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, vector::zero);
        volVectorField pstress_v2(IOobject("post_pstress_v2", runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, vector::zero);
        volVectorField pstress_v3(IOobject("post_pstress_v3", runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, vector::zero);

        forAll(pstress, i) {
            const symmTensor& stress = sigma[i];

            m_eigValues = eigenValues(stress);
            m_eigVectors = eigenVectors(stress);

            sort();
            
            pstress[i] = m_eigValues;
            pstress_v1[i] = m_eigVector_1;
            pstress_v2[i] = m_eigVector_2;
            pstress_v3[i] = m_eigVector_3;
        }

        forAll(mesh.boundaryMesh(), patchI) {
            forAll(mesh.boundary()[patchI], patchFaceI) {
                const symmTensor& stress = sigma.boundaryField()[patchI][patchFaceI];
                m_eigValues = eigenValues(stress);
                m_eigVectors = eigenVectors(stress);

                sort();
                
                pstress.boundaryFieldRef()[patchI][patchFaceI] = m_eigValues;
                
                pstress_v1.boundaryFieldRef()[patchI][patchFaceI] = m_eigVector_1;
                pstress_v2.boundaryFieldRef()[patchI][patchFaceI] = m_eigVector_2;
                pstress_v3.boundaryFieldRef()[patchI][patchFaceI] = m_eigVector_3;
            }
        }

        pstress.write();
        pstress_v1.write();
        pstress_v2.write();
        pstress_v3.write();
    }

};


#endif