#include "fvCFD.H"
#include "transform.H"
#include "processorFvPatch.H"
#include <vector>

int main(int argc, char *argv[])
{
    timeSelector::addOptions();
    argList::validArgs.append("fieldName");
#   include "setRootCase.H"
#   include "createTime.H"
#   include "createMesh.H"

    word fieldName = args[1];
    instantList times = timeSelector::select0(runTime, args);
    forAll(times, timeI)
    {
        runTime.setTime(times[timeI], timeI);
        Info<< "Time = " << runTime.timeName() << endl;
        Info << "field name " << fieldName << endl;

        IOobject fieldHeader
        (
            fieldName,
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        );

        word fieldType("none");

        Info << fieldHeader.name() << endl;
        Info << fieldHeader.headerClassName() << endl;

        if (fieldHeader.typeHeaderOk<surfaceSymmTensorField>(true)) {
            fieldType = "surfaceSymmTensorField";
            Info << "surfaceSymmTensorField" << endl;
        }

        if (fieldHeader.typeHeaderOk<volSymmTensorField>(true)) {
            fieldType = "volSymmTensorField";
            Info << "volSymmTensorField" << endl;
        }

        word fieldTname(fieldName + "_T");
        vector nf0(1, 0, 0);

        if (fieldType == "surfaceSymmTensorField") {
            Info << "field type is surfaceSymmTensorField" << endl;
            surfaceSymmTensorField field(fieldHeader, mesh);
            surfaceSymmTensorField fieldT(IOobject(fieldTname, runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, symmTensor::zero);

            forAll(mesh.boundaryMesh(), patchI) {
                if (!isA<processorFvPatch>(mesh.boundary()[patchI])) {
                    forAll(mesh.boundary()[patchI], patchFaceI) {
                        const label& faceI = mesh.boundaryMesh()[patchI].start() + patchFaceI;
                        const vector& nf = mesh.Sf()[faceI] / mag(mesh.Sf()[faceI]);
                        if (((nf & nf0) > 0.999) || ((nf & nf0) < -0.999)) {
                            fieldT.boundaryFieldRef()[patchI][patchFaceI] = field.boundaryField()[patchI][patchFaceI];
                        } else {
                            tensor T = rotationTensor(nf, nf0);
                            fieldT.boundaryFieldRef()[patchI][patchFaceI] = transform(T, field.boundaryField()[patchI][patchFaceI]);
                        }
                    }
                }
            }
            fieldT.write();


        } else if (fieldType == "volSymmTensorField") {
            Info << "field type is volSymmTensorField" << endl;
            volSymmTensorField field(fieldHeader, mesh);
            volSymmTensorField fieldT(IOobject(fieldTname, runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, symmTensor::zero);

            forAll(mesh.boundaryMesh(), patchI) {
                if (!isA<processorFvPatch>(mesh.boundary()[patchI])) {
                    forAll(mesh.boundary()[patchI], patchFaceI) {
                        const label& faceI = mesh.boundaryMesh()[patchI].start() + patchFaceI;
                        const label& cellI = mesh.faceOwner()[faceI];
                        const vector& nf = mesh.Sf()[faceI] / mag(mesh.Sf()[faceI]);
                        if (((nf & nf0) > 0.999) || ((nf & nf0) < -0.999)) {
                            fieldT[cellI] = field[cellI];
                            fieldT.boundaryFieldRef()[patchI][patchFaceI] = field.boundaryField()[patchI][patchFaceI];
                        } else {
                            tensor T = rotationTensor(nf, nf0);
                            fieldT[cellI] = transform(T, field[cellI]);
                            fieldT.boundaryFieldRef()[patchI][patchFaceI] = transform(T, field.boundaryField()[patchI][patchFaceI]);                            
                        }
                    }
                }
            }
            fieldT.write();

        } else {
            FatalError << "app is implemented only for surfaceSymmTensorField and volSymmTensorField" << nl
                << fieldType + " is used!" << endl;
        }
    }



    Info<< endl << "End" << endl << endl;

    return 0;
}
