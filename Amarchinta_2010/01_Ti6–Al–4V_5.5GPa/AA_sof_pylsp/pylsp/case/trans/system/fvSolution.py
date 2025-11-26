def get(case): return '\
FoamFile\n\
{\n\
    version     2.0;\n\
    format      ascii;\n\
    class       dictionary;\n\
    location    "system";\n\
    object      fvSolution;\n\
}\n\
\n\
solvers\n\
{\n\
    D\n\
    {\n\
        solver diagonal;\n\
    }\n\
}\n\
\n'
