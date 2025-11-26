#include "mapPolyMesh.H"
#include "argList.H"
#include "cellSet.H"
#include "IOobjectList.H"
#include "volFields.H"
#include "fvc.H"
#include "Istream.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "map volume and surface fields from decomposed local problem to orignal mesh (calling from target)"
    );

    argList::noParallel();

    argList::validArgs.append("GlobalCase");
    argList::validArgs.append("LocalCase");
    argList::addBoolOption("inverse");
    argList::addBoolOption("unstructured");

    argList args(argc, argv);

    if (!args.check())
    {
        FatalError.exit();
    }

    bool bInv = args.found("inverse");
    bool bUns = args.found("unstructured");
   
    //create dirs
    fileName GlobalCasePath = args[1];
    const fileName rootDirGlobalCase = GlobalCasePath.path().toAbsolute();
    const fileName caseDirGlobalCase = GlobalCasePath.name();
    Info << "GlobalCase"  << endl << "rootDirGlobalCase: " << rootDirGlobalCase << endl << "caseDirGlobalCase: " << caseDirGlobalCase << endl << endl;

    fileName LocalCasePath = args[2];
    const fileName rootDirLocalCase = LocalCasePath.path().toAbsolute();
    const fileName caseDirLocalCase = LocalCasePath.name();
    Info << "LocalCase" << endl << "rootDirLocalCase: " << rootDirLocalCase << endl << "caseDirLocalCase: " << caseDirLocalCase << endl << endl;


    //create times
    Info << "\nCreate databases as time" << endl;

    setEnv("FOAM_CASE", rootDirGlobalCase/caseDirGlobalCase, true);
    setEnv("FOAM_CASE_NAME", caseDirGlobalCase, true);

    Time runTimeGlobalCase
    (
        Time::controlDictName,
        rootDirGlobalCase,
        caseDirGlobalCase
    );

    setEnv("FOAM_CASE", rootDirLocalCase/caseDirLocalCase, true);
    setEnv("FOAM_CASE_NAME", caseDirLocalCase, true);

    Time runTimeLocalCase
    (
        Time::controlDictName,
        rootDirLocalCase,
        caseDirLocalCase
    );

    //get number of proc dirs
    IOdictionary decompositionDictLocalCase
    (
        IOobject
        (
            "decomposeParDict",
            runTimeLocalCase.system(),
            runTimeLocalCase,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

    int nProcsLocalCase
    (
        readInt(decompositionDictLocalCase.lookup("numberOfSubdomains"))
    );

    IOdictionary decompositionDictGlobalCase
    (
        IOobject
        (
            "decomposeParDict",
            runTimeGlobalCase.system(),
            runTimeGlobalCase,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

    int nProcsGlobalCase
    (
        readInt(decompositionDictGlobalCase.lookup("numberOfSubdomains"))
    );

    Info << endl;
    Info << "nProcsGlobalCase: " << nProcsGlobalCase << endl;
    Info << "nProcsLocalCase:  " << nProcsLocalCase << endl;    

    label timeI = 0;
    instantList times;
    Time* pRunTimeLocalCase[nProcsLocalCase];
    fvMesh* pMeshLocalCase[nProcsLocalCase];
    for (int procILocalCase = 0; procILocalCase<nProcsLocalCase; procILocalCase++)
    {
        pRunTimeLocalCase[procILocalCase] = new Time
        (
            Time::controlDictName,
            rootDirLocalCase,
            caseDirLocalCase/fileName(word("processor") + name(procILocalCase))
        );

        times = pRunTimeLocalCase[procILocalCase]->times();
        timeI = times.size() - 1;
        pRunTimeLocalCase[procILocalCase]->setTime(times[timeI], timeI);

        Info << "Create Local Mesh - processor " << procILocalCase << endl;
        pMeshLocalCase[procILocalCase] = new fvMesh
        (
            IOobject
            (
                fvMesh::defaultRegion,
                pRunTimeLocalCase[procILocalCase]->timeName(),
                *pRunTimeLocalCase[procILocalCase]
            )
        );
    }

    Time* pRunTimeGlobalCase[nProcsGlobalCase];
    fvMesh* pMeshGlobalCase[nProcsGlobalCase];
    for (int procIGlobalCase = 0; procIGlobalCase<nProcsGlobalCase; procIGlobalCase++)
    {
        pRunTimeGlobalCase[procIGlobalCase] = new Time
        (
            Time::controlDictName,
            rootDirGlobalCase,
            caseDirGlobalCase/fileName(word("processor") + name(procIGlobalCase))
        );

        pRunTimeGlobalCase[procIGlobalCase]->setTime(times[timeI], timeI);

        Info << "Create Global Mesh - processor " << procIGlobalCase << endl;
        pMeshGlobalCase[procIGlobalCase] = new fvMesh
        (
            IOobject
            (
                fvMesh::defaultRegion,
                pRunTimeGlobalCase[procIGlobalCase]->timeName(),
                *pRunTimeGlobalCase[procIGlobalCase]
            )
        );
    }

    for (int procILocalCase = 0; procILocalCase < nProcsLocalCase; procILocalCase++)
    {
        volSymmTensorField epsilonP_l
        (
            IOobject
            (
                "epsilonP",
                pRunTimeLocalCase[procILocalCase]->timeName(),
                *pMeshLocalCase[procILocalCase],
                IOobject::READ_IF_PRESENT,
                IOobject::NO_WRITE
            ),
            *pMeshLocalCase[procILocalCase]
        );

        surfaceSymmTensorField epsilonPf_l
        (
            IOobject
            (
                "epsilonPf",
                pRunTimeLocalCase[procILocalCase]->timeName(),
                *pMeshLocalCase[procILocalCase],
                IOobject::READ_IF_PRESENT,
                IOobject::NO_WRITE
            ),
            *pMeshLocalCase[procILocalCase]
        );

        volVectorField D_l
        (
            IOobject
            (
                "D",
                pRunTimeLocalCase[procILocalCase]->timeName(),
                *pMeshLocalCase[procILocalCase],
                IOobject::READ_IF_PRESENT,
                IOobject::NO_WRITE
            ),
            *pMeshLocalCase[procILocalCase]
        );


        IOList<label> procGlobalCaseList
        (
            IOobject
            (
                "procGlobalCaseList",
                pRunTimeLocalCase[procILocalCase]->constant(),
                "polyMesh/maps",
                *pMeshLocalCase[procILocalCase],
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            )
        );

        int nProcsGlobalCase = procGlobalCaseList.size();

        for (int procIGlobalCase = 0; procIGlobalCase < nProcsGlobalCase; procIGlobalCase++)
        {
            const label& procLGlobalCase = procGlobalCaseList[procIGlobalCase];

            IOList<label> faceMap
            (
                IOobject
                (
                    "faceMap",
                    pRunTimeLocalCase[procILocalCase]->constant(),
                    "polyMesh/maps/processor" + name(procLGlobalCase),
                    *pMeshLocalCase[procILocalCase],
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE
                )
            );

            IOList<label> cellMap
            (
                IOobject
                (
                    "cellMap",
                    pRunTimeLocalCase[procILocalCase]->constant(),
                    "polyMesh/maps/processor" + name(procLGlobalCase),
                    *pMeshLocalCase[procILocalCase],
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE
                )
            );
            if (!bInv) { //local2global
                volSymmTensorField epsilonP_g
                (
                    IOobject
                    (
                        "epsilonP",
                        pRunTimeGlobalCase[procLGlobalCase]->timeName(),
                        *pMeshGlobalCase[procLGlobalCase],
                        IOobject::MUST_READ,
                        IOobject::NO_WRITE
                    ),
                    *pMeshGlobalCase[procLGlobalCase]
                );

                Info << "MAPING: epsilonP local " << procILocalCase << "(" << epsilonP_l.size() << ") -> global " << procLGlobalCase << "(" << epsilonP_g.size() << ")" << endl;

                Info << "        local cells to global cells..." << endl;
                forAll(epsilonP_l, cellI) {
                    if (cellMap[cellI] >= 0) {
                        epsilonP_g[cellMap[cellI]] = epsilonP_l[cellI];
                    }
                }           

                Info << "        local boundary faces to global boundary faces (exclude global processor patches) ..." << endl;
                forAll(pMeshLocalCase[procILocalCase]->boundary(), patchIL) {
                    Info << pMeshLocalCase[procILocalCase]->boundary()[patchIL].name() << endl;
                    forAll(pMeshLocalCase[procILocalCase]->boundary()[patchIL], patchFaceIL) {
                        const label& faceIL = pMeshLocalCase[procILocalCase]->boundaryMesh()[patchIL].start() + patchFaceIL;
                        const label& faceIG = faceMap[faceIL];
                        if (faceIG >= 0) {
                            if (!pMeshGlobalCase[procLGlobalCase]->isInternalFace(faceIG)) {
                                const label& patchIG = pMeshGlobalCase[procLGlobalCase]->boundaryMesh().whichPatch(faceIG);
                                const label& patchFaceIG = pMeshGlobalCase[procLGlobalCase]->boundaryMesh()[patchIG].whichFace(faceIG);
                                epsilonP_g.boundaryFieldRef()[patchIG][patchFaceIG] = epsilonP_l.boundaryField()[patchIL][patchFaceIL];
                            }
                        }
                    }
                }

                IStringStream schemeData("linear");
                surfaceSymmTensorField epsilonPf_l(fvc::interpolate(epsilonP_l, schemeData));

                Info << "        local internal faces to global processor patches ..." << endl;
                forAll(epsilonPf_l, faceIL) {
                    const label& faceIG = faceMap[faceIL];
                    if (faceIG >= 0) {
                        if (!pMeshGlobalCase[procLGlobalCase]->isInternalFace(faceIG)) {
                            const label& patchIG = pMeshGlobalCase[procLGlobalCase]->boundaryMesh().whichPatch(faceIG);
                            const label& patchFaceIG = pMeshGlobalCase[procLGlobalCase]->boundaryMesh()[patchIG].whichFace(faceIG);
                            epsilonP_g.boundaryFieldRef()[patchIG][patchFaceIG] = epsilonPf_l[faceIL];
                        }
                    }
                }

                epsilonP_g.write();

                if (bUns) {
                    surfaceSymmTensorField epsilonPf_g
                    (
                        IOobject
                        (
                            "epsilonPf",
                            pRunTimeGlobalCase[procLGlobalCase]->timeName(),
                            *pMeshGlobalCase[procLGlobalCase],
                            IOobject::MUST_READ,
                            IOobject::NO_WRITE
                        ),
                        *pMeshGlobalCase[procLGlobalCase]
                    );

                    Info << "MAPING: epsilonPf local " << procILocalCase << "(" << epsilonPf_l.size() << ") -> global " << procLGlobalCase << "(" << epsilonPf_g.size() << ")" << endl;
                    
                    Info << "        local internal faces to global internal faces (including global processor faces)..." << endl;
                    forAll(epsilonPf_l, faceIL) {
                        const label& faceIG = faceMap[faceIL];
                        if (faceIG >= 0) {
                            if (pMeshGlobalCase[procLGlobalCase]->isInternalFace(faceIG)) {
                                epsilonPf_g[faceIG] = epsilonPf_l[faceIL];
                            } else {
                                const label& patchIG = pMeshGlobalCase[procLGlobalCase]->boundaryMesh().whichPatch(faceIG);
                                const label& patchFaceIG = pMeshGlobalCase[procLGlobalCase]->boundaryMesh()[patchIG].whichFace(faceIG);
                                epsilonPf_g.boundaryFieldRef()[patchIG][patchFaceIG] = epsilonPf_l[faceIL];
                            }
                        }
                    }

                    Info << "        local boundary faces to global boundary faces (exclude global processor patches)..." << endl;
                    forAll(pMeshLocalCase[procILocalCase]->boundary(), patchIL) {
                        Info << pMeshLocalCase[procILocalCase]->boundary()[patchIL].name() << endl;
                        forAll(pMeshLocalCase[procILocalCase]->boundary()[patchIL], patchFaceIL) {
                            const label& faceIL = pMeshLocalCase[procILocalCase]->boundaryMesh()[patchIL].start() + patchFaceIL;
                            const label& faceIG = faceMap[faceIL];
                            if (faceIG >= 0) {
                                if (pMeshGlobalCase[procLGlobalCase]->isInternalFace(faceIG)) {
                                    epsilonPf_g[faceIG] = epsilonPf_l.boundaryField()[patchIL][patchFaceIL];
                                } else {
                                    const label& patchIG = pMeshGlobalCase[procLGlobalCase]->boundaryMesh().whichPatch(faceIG);
                                    const label& patchFaceIG = pMeshGlobalCase[procLGlobalCase]->boundaryMesh()[patchIG].whichFace(faceIG);
                                    epsilonPf_g.boundaryFieldRef()[patchIG][patchFaceIG] = epsilonPf_l.boundaryField()[patchIL][patchFaceIL];
                                }
                            }
                        }
                    }

                    epsilonPf_g.write();
                }
            } else {
                volVectorField D_g
                (
                    IOobject
                    (
                        "D",
                        pRunTimeGlobalCase[procLGlobalCase]->timeName(),
                        *pMeshGlobalCase[procLGlobalCase],
                        IOobject::MUST_READ,
                        IOobject::NO_WRITE
                    ),
                    *pMeshGlobalCase[procLGlobalCase]
                );

                Info << "MAPING: D global " << procLGlobalCase << "(" << D_g.size() << ") -> local " << procILocalCase << "(" << D_l.size() << ")" << endl;

                Info << "        local cells from global cells..." << endl;
                forAll(D_l, cellI) {
                    if (cellMap[cellI] >= 0) {
                        D_l[cellI] = D_g[cellMap[cellI]];
                    }
                }

                IStringStream schemeData("linear");
                surfaceVectorField Df_g(fvc::interpolate(D_g, schemeData));

                Info << "        local boundary faces from global internal and boundary faces..." << endl;
                forAll(pMeshLocalCase[procILocalCase]->boundary(), patchIL) {
                    Info << pMeshLocalCase[procILocalCase]->boundary()[patchIL].name() << endl;
                    forAll(pMeshLocalCase[procILocalCase]->boundary()[patchIL], patchFaceIL) {
                        const label& faceIL = pMeshLocalCase[procILocalCase]->boundaryMesh()[patchIL].start() + patchFaceIL;
                        const label& faceIG = faceMap[faceIL];
                        if (faceIG >= 0) {
                            if (pMeshGlobalCase[procLGlobalCase]->isInternalFace(faceIG)) {
                                D_l.boundaryFieldRef()[patchIL][patchFaceIL] = Df_g[faceIG];
                            } else {
                                const label& patchIG = pMeshGlobalCase[procLGlobalCase]->boundaryMesh().whichPatch(faceIG);
                                const label& patchFaceIG = pMeshGlobalCase[procLGlobalCase]->boundaryMesh()[patchIG].whichFace(faceIG);
                                D_l.boundaryFieldRef()[patchIL][patchFaceIL] = D_g.boundaryField()[patchIG][patchFaceIG];
                            }
                        }
                    }
                }
            }
        }
        D_l.write();
    }

    for (int procILocalCase = 0; procILocalCase<nProcsLocalCase; procILocalCase++)
    {
        delete pMeshLocalCase[procILocalCase];
        delete pRunTimeLocalCase[procILocalCase];
    }

    for (int procIGlobalCase = 0; procIGlobalCase<nProcsGlobalCase; procIGlobalCase++)
    {
        delete pMeshGlobalCase[procIGlobalCase];
        delete pRunTimeGlobalCase[procIGlobalCase];
    }    

    Info << nl << "End" << endl;

    return 0;
}
