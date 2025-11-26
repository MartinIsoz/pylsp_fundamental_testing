#include "fvCFD.H"

int main(int argc, char *argv[])
{
#   include "setRootCase.H"
#   include "createTime.H"
#   include "createMesh.H"

    surfaceSymmTensorField epsilonPf(IOobject("epsilonPf", runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, symmTensor::zero);
    epsilonPf.write();

    volSymmTensorField     epsilonP (IOobject("epsilonP",  runTime.timeName(), mesh, IOobject::NO_READ, IOobject::NO_WRITE), mesh, symmTensor::zero);
    epsilonP.write();

    Info<< endl << "End" << endl << endl;

    return 0;
}
