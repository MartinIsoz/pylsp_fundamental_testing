import pylsp

def get(case):

    answ = '\
FoamFile\n\
{\n\
    version     2.0;\n\
    format      ascii;\n\
    class       dictionary;\n\
    location    "constant";\n\
    object      mechanicalProperties;\n\
}\n\
\n\
planeStress no;\n\
\n\
mechanical\n\
(\n\
    steel\n\
    {\n\
        rho  rho [1 -3 0 0 0 0 0]  ' + str(case.lsp.material.rho) + ';\n\
        E    E   [1 -1 -2 0 0 0 0] ' + str(case.lsp.material.E) + ';\n\
        nu   nu  [0 0 0 0 0 0 0]   ' + str(case.lsp.material.nu) + ';\n\
        solvePressureEqn no;\n'

    if isinstance(case.lsp.material, pylsp.LinearElasticMaterial):
        answ += '\
        type linearElastic;\n'
    elif isinstance(case.lsp.material, pylsp.MisesIdealPlasticsMaterial):
        answ += '\
        type linearElasticMisesPlastic;\n\
        "file|fileName" "$FOAM_CASE/constant/plasticStrainVsYieldStress";\n\
        outOfBounds     clamp;\n'
    elif isinstance(case.lsp.material, pylsp.JohnsonCookPlasticsMaterial):
        answ += '\
        type linearElasticMisesPlasticJC;\n\
        A       ' + str(case.lsp.material.A) + ';\n\
        B       ' + str(case.lsp.material.B) + ';\n\
        C       ' + str(case.lsp.material.C) + ';\n\
        n       ' + str(case.lsp.material.n) + ';\n\
        epsDot0 ' + str(case.lsp.material.epsDot0) + ';\n'
    elif isinstance(case.lsp.material, pylsp.LimHuhPlasticsMaterial):
        answ += '\
        type linearElasticMisesPlasticLH;\n\
        K       ' + str(case.lsp.material.K) + ';\n\
        eps0    ' + str(case.lsp.material.eps0) + ';\n\
        n       ' + str(case.lsp.material.n) + ';\n\
        q1      ' + str(case.lsp.material.q1) + ';\n\
        q2      ' + str(case.lsp.material.q2) + ';\n\
        q3      ' + str(case.lsp.material.q3) + ';\n\
        p       ' + str(case.lsp.material.p) + ';\n\
        epsDot0 ' + str(case.lsp.material.epsDot0) + ';\n'

    answ += '\
    }\n\
);'

    return answ
