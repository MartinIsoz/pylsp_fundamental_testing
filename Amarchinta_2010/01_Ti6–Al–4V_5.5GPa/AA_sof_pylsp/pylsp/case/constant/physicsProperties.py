def get(case): return '\
FoamFile\n\
{\n\
    version     2.0;\n\
    format      ascii;\n\
    class       dictionary;\n\
    location    "constant";\n\
    object      physicsProperties;\n\
}\n\
\n\
type solid;'