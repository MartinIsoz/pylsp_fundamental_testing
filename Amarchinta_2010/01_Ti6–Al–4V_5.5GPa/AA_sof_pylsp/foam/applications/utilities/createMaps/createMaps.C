#include "mapPolyMesh.H"
#include "argList.H"
#include "cellSet.H"
#include "IOobjectList.H"
#include "volFields.H"

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

    argList args(argc, argv);

    if (!args.check())
    {
        FatalError.exit();
    }
   
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

    unsigned int nProcsGlobalCase
    (
        readInt(decompositionDictGlobalCase.lookup("numberOfSubdomains"))
    );


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

    unsigned int nProcsLocalCase
    (
        readInt(decompositionDictLocalCase.lookup("numberOfSubdomains"))
    );

    Info << endl;
    Info << "nProcsGlobalCase: " << nProcsGlobalCase << endl;
    Info << "nProcsLocalCase:  " << nProcsLocalCase << endl;

    List<boundBox> bbsGlobalCase(nProcsGlobalCase);
    List<bool> bbsGlobalCaseSet(nProcsGlobalCase, false);
    Time* pRunTimeGlobalCase[nProcsGlobalCase];
    fvMesh* pMeshGlobalCase[nProcsGlobalCase];

    for (unsigned int procIGlobalCase = 0; procIGlobalCase < nProcsGlobalCase; procIGlobalCase++)
    {
        pRunTimeGlobalCase[procIGlobalCase] = new Time
        (
            Time::controlDictName,
            rootDirGlobalCase,
            caseDirGlobalCase/fileName(word("processor") + name(procIGlobalCase))
        );

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
    
    for (unsigned int procILocalCase = 0; procILocalCase < nProcsLocalCase; procILocalCase++)
    {
        Time runTimeLocalCase
        (
            Time::controlDictName,
            rootDirLocalCase,
            caseDirLocalCase/fileName(word("processor") + name(procILocalCase))
        );

        Info << "Create Local Mesh - processor " << procILocalCase << endl;
        fvMesh meshLocalCase
        (
            IOobject
            (
                fvMesh::defaultRegion,
                runTimeLocalCase.timeName(),
                runTimeLocalCase
            )
        );
     
        boundBox bbLocalCase(meshLocalCase.bounds());


        IOList<label> procGlobalCaseList
            (
                IOobject
                (
                    "procGlobalCaseList",
                    runTimeLocalCase.constant(),
                    "polyMesh/maps",
                    meshLocalCase,
                    IOobject::NO_READ,
                    IOobject::AUTO_WRITE
                )
            );
        for (unsigned int procIGlobalCase = 0; procIGlobalCase < nProcsGlobalCase; procIGlobalCase++)
        {
            if
            (
                (pMeshGlobalCase[procIGlobalCase]->nCells() > 0)
                &&
                (!bbsGlobalCaseSet[procIGlobalCase] || (bbsGlobalCaseSet[procIGlobalCase] && bbsGlobalCase[procIGlobalCase].overlaps(bbLocalCase)))
            )
            {
                bbsGlobalCase[procIGlobalCase] = pMeshGlobalCase[procIGlobalCase]->bounds();
                bbsGlobalCaseSet[procIGlobalCase] = true;

                if (bbsGlobalCase[procIGlobalCase].overlaps(bbLocalCase))
                {
                    Info << "MAPING: Local " << procILocalCase << "(" << meshLocalCase.nCells() << ") -> Global " << procIGlobalCase << "(" << pMeshGlobalCase[procIGlobalCase]->nCells() << ")" << endl;

                    IOList<label> faceMap1
                    (
                        IOobject
                        (
                            "faceMap",
                            runTimeGlobalCase.constant() + "/polyMesh",
                            *pMeshGlobalCase[procIGlobalCase],
                            IOobject::MUST_READ,
                            IOobject::NO_WRITE
                        )
                    );

                    IOList<label> cellMap1
                    (
                        IOobject
                        (
                            "cellMap",
                            runTimeGlobalCase.constant() + "/polyMesh",
                            *pMeshGlobalCase[procIGlobalCase],
                            IOobject::MUST_READ,
                            IOobject::NO_WRITE
                        )
                    );

                    IOList<label> faceProcAddressing1
                    (
                        IOobject
                        (
                            "faceProcAddressing",
                            runTimeGlobalCase.constant() + "/polyMesh",
                            *pMeshGlobalCase[procIGlobalCase],
                            IOobject::MUST_READ,
                            IOobject::NO_WRITE
                        )
                    );

                    forAll (faceProcAddressing1, i) {
                        if (faceProcAddressing1[i] < 0) {
                            faceProcAddressing1[i] = mag(faceProcAddressing1[i]);
                        }
                    }

                    IOList<label> cellProcAddressing1
                    (
                        IOobject
                        (
                            "cellProcAddressing",
                            runTimeGlobalCase.constant() + "/polyMesh",
                            *pMeshGlobalCase[procIGlobalCase],
                            IOobject::MUST_READ,
                            IOobject::NO_WRITE
                        )
                    );

                    IOList<label> faceProcAddressing2
                    (
                        IOobject
                        (
                            "faceProcAddressing",
                            runTimeLocalCase.constant() + "/polyMesh",
                            meshLocalCase,
                            IOobject::MUST_READ,
                            IOobject::NO_WRITE
                        )
                    );

                    forAll (faceProcAddressing2, i) {
                        if (faceProcAddressing2[i] < 0) {
                            faceProcAddressing2[i] = mag(faceProcAddressing2[i]);
                        }
                    }

                    IOList<label> cellProcAddressing2
                    (
                        IOobject
                        (
                            "cellProcAddressing",
                            runTimeLocalCase.constant() + "/polyMesh",
                            meshLocalCase,
                            IOobject::MUST_READ,
                            IOobject::NO_WRITE
                        )
                    );

                    label maxGlobalI = max(faceProcAddressing1) + 1;
                    labelList faceProcAddressing1inv(maxGlobalI, -1);
                    forAll(faceProcAddressing1, localI) {
                        label globalI = faceProcAddressing1[localI];
                        faceProcAddressing1inv[globalI] = localI;
                    }

                    bool mapExists = false;
                    labelList faceMap(faceProcAddressing2.size(), -1);
                    forAll(faceMap, faceMapI) {
                        label reconstructedLocal = faceProcAddressing2[faceMapI];
                        if (reconstructedLocal >= maxGlobalI) {
                            continue;
                        }
                        if (faceProcAddressing1inv[reconstructedLocal] > -1) {
                            label decomposedLocalOnGlobal = faceProcAddressing1inv[reconstructedLocal];
                            label decomposedGlobal = faceMap1[decomposedLocalOnGlobal];
                            if (decomposedGlobal >= 0) {
                                mapExists = true;
                            }
                            faceMap[faceMapI] = decomposedGlobal;
                        }
                    }

                    maxGlobalI = max(cellProcAddressing1) + 1;
                    labelList cellProcAddressing1inv(maxGlobalI, -1);
                    forAll(cellProcAddressing1, localI) {
                        label globalI = cellProcAddressing1[localI];
                        cellProcAddressing1inv[globalI] = localI;
                    }

                    labelList cellMap(cellProcAddressing2.size(), -1);
                    forAll(cellMap, cellMapI) {
                        label reconstructedLocal = cellProcAddressing2[cellMapI];
                        if (reconstructedLocal >= maxGlobalI) {
                            continue;
                        }
                        if (cellProcAddressing1inv[reconstructedLocal] > -1) {
                            label decomposedLocalOnGlobal = cellProcAddressing1inv[reconstructedLocal];
                            label decomposedGlobal = cellMap1[decomposedLocalOnGlobal];
                            if (decomposedGlobal >= 0) {
                                mapExists = true;
                            }
                            cellMap[cellMapI] = decomposedGlobal;
                        }
                    }

                    if (mapExists) {
                        IOList<label> finalFaceMap
                        (
                            IOobject
                            (
                                "faceMap",
                                runTimeLocalCase.constant(),
                                "polyMesh/maps/processor" + name(procIGlobalCase),
                                meshLocalCase,
                                IOobject::NO_READ,
                                IOobject::AUTO_WRITE
                            ),
                            faceMap
                        );
                        finalFaceMap.write();

                        IOList<label> finalCellMap
                        (
                            IOobject
                            (
                                "cellMap",
                                runTimeLocalCase.constant(),
                                "polyMesh/maps/processor" + name(procIGlobalCase),
                                meshLocalCase,
                                IOobject::NO_READ,
                                IOobject::AUTO_WRITE
                            ),
                            cellMap
                        );
                        finalCellMap.write();
                        
                        procGlobalCaseList.append(procIGlobalCase);
                    }
                }
            }
        }
        procGlobalCaseList.write();
    }

    for (unsigned int procIGlobalCase = 0; procIGlobalCase < nProcsGlobalCase; procIGlobalCase++)
    {
        delete pMeshGlobalCase[procIGlobalCase];
        delete pRunTimeGlobalCase[procIGlobalCase];
    }    

    Info << nl << "End" << endl;

    return 0;
}
