def get(case):

    header = '\
FoamFile\n\
{\n\
    version     2.0;\n\
    format      ascii;\n\
    class       dictionary;\n\
    location    "system";\n\
    object      fvSolution;\n\
}\n\
\n'

    if (case.lsp.fvSolution.solver == 'GAMG'):
        solvers = '\
solvers\n\
{\n\
    "D|DD"\n\
    {\n\
        solver         ' + case.lsp.fvSolution.solver + ';\n\
        agglomerator   ' + case.lsp.fvSolution.agglomerator + ';\n\
        mergeLevels    ' + str(case.lsp.fvSolution.mergeLevels) + ';\n\
        cacheAgglomeration ' + case.lsp.fvSolution.cacheAgglomeration + ';\n\
        nCellsInCoarsestLevel ' + str(case.lsp.fvSolution.nCellsInCoarsestLevel) + ';\n\
        tolerance      ' + str(case.lsp.fvSolution.tolerance) + ';\n\
        relTol         ' + str(case.lsp.fvSolution.relTol) + ';\n\
        smoother       ' + case.lsp.fvSolution.smoother + ';\n\
        nPreSweeps     ' + str(case.lsp.fvSolution.nPreSweeps) + ';\n\
        nPostSweeps    ' + str(case.lsp.fvSolution.nPostSweeps) + ';\n\
        nFinestSweeps  ' + str(case.lsp.fvSolution.nFinestSweeps) + ';\n\
        minIter        ' + str(case.lsp.fvSolution.minIter) + ';\n\
    }\n\
}\n\
\n'
    else:
        solvers = '\
solvers\n\
{\n\
    "D|DD"\n\
    {\n\
        solver         ' + case.lsp.fvSolution.solver + ';\n\
        preconditioner ' + case.lsp.fvSolution.preconditioner + ';\n\
        tolerance      ' + str(case.lsp.fvSolution.tolerance) + ';\n\
        relTol         ' + str(case.lsp.fvSolution.relTol) + ';\n\
    }\n\
}\n\
\n'

    factors = '\
relaxationFactors\n\
{}'

    return header + solvers + factors
