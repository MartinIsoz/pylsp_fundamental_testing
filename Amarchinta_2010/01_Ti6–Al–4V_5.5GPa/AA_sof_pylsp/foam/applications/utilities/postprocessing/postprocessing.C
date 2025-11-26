#include "fvCFD.H"
#include "processorFvPatch.H"
#include <vector>
#include "pstress.H"
#include "sigmaEq.H"
#include "epsilonEq.H"
#include "epsilonPEq.H"



int main(int argc, char *argv[])
{
    timeSelector::addOptions();

    argList::validOptions.insert(
        "fieldNames",
        "const string& param = "
    );

#   include "setRootCase.H"
#   include "createTime.H"
#   include "createMesh.H"

    wordList fieldNames = args.optionRead<wordList>("fieldNames");

    List<CalcField*> pCalcFields;

    forAll(fieldNames, i) {
        word fieldName = fieldNames[i];

        if (fieldName == "pstress") {
            pCalcFields.append(new PrincipalStress());
        } else if (fieldName == "sigmaEq") {
            pCalcFields.append(new SigmaEq());
        } else if (fieldName == "epsilonEq") {
            pCalcFields.append(new EpsilonEq());
        } else if (fieldName == "epsilonPEq") {
            pCalcFields.append(new EpsilonPEq());
        } else {
            Info << "NOT implemented for " << fieldName << endl << endl;
            continue;
        }
    }

    if (pCalcFields.size() < 1) {
        Info << "NO fields for calculation" << endl << endl;
        return 0;
    }

    instantList times = timeSelector::select0(runTime, args);

    Info<< endl << "Start" << endl << endl;

    forAll(times, timeI)
    {
        runTime.setTime(times[timeI], timeI);
        Info<< "XXXXXXXXXXXXXXXXXXXXXXXX" << endl;
        Info<< "Time = " << runTime.timeName() << endl;
        Info<< "XXXXXXXXXXXXXXXXXXXXXXXX" << endl;

        forAll(pCalcFields, i) {
            pCalcFields[i]->calc(runTime, mesh);
        }
    }

    Info<< endl << "End" << endl << endl;

    return 0;
}
