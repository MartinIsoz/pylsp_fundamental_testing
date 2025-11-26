import pylsp


def get(case):
    answ = ''
    if isinstance(case.lsp.material, pylsp.MisesIdealPlasticsMaterial):
        answ += '( ( 0.0 ' + str(case.lsp.material.fy) + ' ) ( 1000.0 ' + str(case.lsp.material.fy) + ' ) )'
    return answ
