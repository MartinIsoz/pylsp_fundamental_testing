def get(case):
    return '\
FoamFile\n\
{\n\
    version     2.0;\n\
    format      ascii;\n\
    class       dictionary;\n\
    location    "system";\n\
    object      cellSetDict;\n\
}\n\n\
actions\n\
(\n\
    {\n\
        name    subproblem;\n\
        type    cellSet;\n\
        action  new;\n\
        source  zoneToCell;\n\
        sourceInfo\n\
        {\n\
            zone subproblem;\n\
        }\n\
    }\n\
);\n'