def get(case):
    if case.lsp.unstructuredApproach:
        solver = 'myExplicitUnsLinearGeometryTotalDisplacement'
    else:
        solver = 'myExplicitLinearGeometryTotalDisplacement'

    return '\
FoamFile\n\
{\n\
    version     2.0;\n\
    format      ascii;\n\
    class       dictionary;\n\
    location    "constant";\n\
    object      solidProperties;\n\
}\n\
\n\
solidModel ' + solver + ';\n\n' + solver + 'Coeffs\n\
{\n\
    linearBulkViscosityCoeff 0.0;\n\
    JSTScaleFactor   0.01;\n\
    numericalViscosity    eta [ 0 0 -1 0 0 0 0 ] 0.0;\n\
}'
