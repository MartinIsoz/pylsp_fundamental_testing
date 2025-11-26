from os import makedirs, path, remove, rename, listdir, symlink
from shutil import copyfile, copytree, move, rmtree
from pylsp.case.case import Case
import pylsp.case as case
import pylsp.case.draft.system as system
import pylsp.case.draft.constant as constant

class Draft(Case):
    def __init__(self, solverDir, lsp, meshCase):
        super().__init__(solverDir, lsp, 'DRAFT')
        self._copyMesh(meshCase)
        self._writeParaviewFoamFile()
        self._initialize()

    def _copyMesh(self, meshCase):
        meshPolyMesh = path.join(meshCase, 'constant', 'polyMesh')
        casePolyMesh = path.join(self._constantDir, 'polyMesh')
        copytree(meshPolyMesh, casePolyMesh)

    def _initialize(self):
        makedirs(path.join(self._caseDir, '0'))
        copyfile(self.lsp.BCfile, path.join(self._caseDir, '0', 'D'))

    def _preSolve(self):
        self._updateLaserBeam()
        self._updateCase(self._step, self._step + 1,
            [
                case.system.fvSchemes,
                case.constant.physicsProperties,
                case.constant.dynamicMeshDict,
                case.constant.g,

                system.fvSolution,
                system.controlDict,
                constant.solidProperties,
                constant.laserBeamProperties,
                constant.mechanicalProperties
            ])

    def solve(self, step):
        self._step = step
        self._preSolve()
        self._runFoamApp(self.lsp.system.foam_com, path.join(self._lspfoamDir, 'lspfoam'), parallel=False)
        self._postSolve()

    def _postSolve(self):
        pass