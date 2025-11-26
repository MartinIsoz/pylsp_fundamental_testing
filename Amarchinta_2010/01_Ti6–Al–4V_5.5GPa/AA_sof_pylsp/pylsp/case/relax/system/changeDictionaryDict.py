def get(case): return '\
FoamFile\n\
{\n\
    version     2.0;\n\
    format      ascii;\n\
    class       dictionary;\n\
    object      changeDictionaryDict;\n\
}\n\
\n\
boundary\n\
{\n\
    oldInternalFaces\n\
    {\n\
        type patch;\n\
        ~inGroups;\n\
    }\n\
}\n\
\n\
"epsilonPf"\n\
{\n\
    boundaryField\n\
    {\n\
        oldInternalFaces\n\
        {\n\
            type fixedValue;\n\
            value uniform (0 0 0 0 0 0);\n\
        }\n\
    }\n\
}\n\
"epsilonP"\n\
{\n\
    boundaryField\n\
    {\n\
        oldInternalFaces\n\
        {\n\
            type fixedValue;\n\
            value uniform (0 0 0 0 0 0);\n\
        }\n\
    }\n\
}\n\
"D"\n\
{\n\
    boundaryField\n\
    {\n\
        oldInternalFaces\n\
        {\n\
            type calculated;\n\
            value uniform (0 0 0);\n\
        }\n\
    }\n\
}\n\
\n'
