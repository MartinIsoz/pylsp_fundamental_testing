from os import listdir

def get(case): return '\
FoamFile\n\
{\n\
    version     2.0;\n\
    format      ascii;\n\
    class       dictionary;\n\
    note        "mesh decomposition control dictionary";\n\
    object      decomposeParDict;\n\
}\n\
\n\
numberOfSubdomains ' + str(case._numberOfProcessors) + ';\n\
\n\
method          manual;\n\
\n\
manualCoeffs\n\
{\n\
    dataFile "manualDecompData";\n\
}'

