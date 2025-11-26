from os import mkdir, path, makedirs, remove, rename, terminal_size, symlink, listdir
from shutil import copytree, copyfile, rmtree, move
from pylsp.case.case import Case
import pylsp.case as case
import pylsp.case.relax.system as system
import pylsp.case.relax.constant as constant

class Relax(Case):
    def __init__(self, solverDir, lsp):
        super().__init__(solverDir, lsp, 'RELAX')
        self._initWriteFields(['D', 'epsilonP', 'epsilonPf'])
        self._transCaseDir = path.join(self._solverDir, 'TRANS')
        self._transCaseConstantDir = path.join(self._transCaseDir, 'constant')
        self._copyMesh()
        self._writeParaviewFoamFile()
        self._initialize()

    def _initialize(self):
        makedirs(path.join(self._caseDir, '0'))
        copyfile(self.lsp.BCfile, path.join(self._caseDir, '0', 'D'))
        self._updateCase(self._step, self._step + 1,
            [
                case.system.fvSchemes,
                case.constant.physicsProperties,
                case.constant.dynamicMeshDict,
                case.constant.g,

                system.fvSolution,
                system.controlDict,
                system.topoSetDict,
                system.changeDictionaryDict,
                system.decomposeParDict,
                constant.solidProperties,
                constant.mechanicalProperties
            ])

        self._decomposePar()
        self._runFoamApp(self.lsp.system.foam_com, path.join(self._lspfoamDir, 'initCase'), parallel=True)

        if not self._isSubproblem():
            return

        self._topoSet()
        self._subsetMesh()
        if self._isParallel():
            self._copyCaseFileToProcessorDirFiles('system', path.join('system', 'setSubset'), 'changeDictionaryDict')
            self._copyCaseFileToProcessorDirFiles('system', path.join('system', 'setSubset'), 'fvSchemes')
            self._copyCaseFileToProcessorDirFiles('system', path.join('system', 'setSubset'), 'fvSolution')
            self._manipulateFilesFromCaseToCase(self._caseDir, '1', self._caseDir, path.join('1', 'polyMesh'), files=['pointMap', 'faceMap', 'cellMap', 'patchMap'], operation=move)
            self._manipulateCaseToCase(self._caseDir, '1', self._caseDir, 'setSubset', operation=move)
            self._manipulateCaseToCase(self._caseDir, 'setSubset', self._caseDir, path.join('1', 'setSubset'), operation=move)
        else:
            copyfile(path.join(self._caseDir, 'system', 'changeDictionaryDict'), path.join(self._caseDir, 'system', 'setSubset', 'changeDictionaryDict'))
        self._changeDictionary()
        self._manipulateFilesFromCaseToCase(self._caseDir, path.join('1', 'setSubset', 'polyMesh'), self._transCaseDir, path.join('constant', 'polyMesh'), operation=move)
        self._manipulateFilesFromCaseToCase(self._caseDir, path.join('1', 'setSubset'), self._transCaseDir, '0', operation=move)
        self._manipulateFilesFromCaseToCase(self._caseDir, '1', operation=rmtree)
        if self._isParallel():
            self._manipulateFilesFromCaseToCase(self._caseDir, path.join('system'), operation=rmtree)
            rmtree(path.join(self._caseDir, 'constant', 'polyMesh'))
            rmtree(path.join(self._caseDir, '0'))

    def _copyMesh(self):
        meshPolyMesh = path.join(self.lsp.meshCase, 'constant', 'polyMesh')
        casePolyMesh = path.join(self._constantDir, 'polyMesh')
        copytree(meshPolyMesh, casePolyMesh)

    def _preSolve(self):
        startTimeDir = self._getTimeDirName(self._transCaseDir, self._step + self._lsp.transientAnalysis.endTime)
        self._updateCase(self._step + self._lsp.transientAnalysis.endTime, self._step + 1,
            [
                case.system.fvSchemes,
                case.constant.physicsProperties,
                case.constant.dynamicMeshDict,
                case.constant.g,

                system.fvSolution,
                system.controlDict,
                system.decomposeParDict,
                constant.solidProperties,
                constant.mechanicalProperties
            ])
        if self._isSubproblem():
            self._manipulateFilesFromCaseToCase(self._caseDir, str(self._step), self._caseDir, startTimeDir, files=['epsilonP', 'epsilonPf'], operation=copyfile)
            self._copyCaseFileToProcessorDirFiles('system', 'system', 'fvSchemes')
            #self._copyCaseFileToProcessorDirFiles('system', 'system', 'fvSchemes', caseDir=self._transCaseDir)
            self._local2global(self._caseDir, self._transCaseDir)
        else:
            self._manipulateFilesFromCaseToCase(self._transCaseDir, startTimeDir, self._caseDir, startTimeDir, files=['epsilonP', 'epsilonPf'], operation=copyfile)

        self._manipulateFilesFromCaseToCase(self._caseDir, '0', self._caseDir, startTimeDir, files=['D'], operation=copyfile)

    def solve(self, step):
        self._step = step
        self._preSolve()
        self._runFoamApp(self.lsp.system.foam_com, path.join(self._lspfoamDir, 'lspfoam'), parallel=True)

        self._letOnlyTheseFields(self._caseDir, self._step, self._step + 1, fields=self._writeFields)
        self._postSolve()

    def _postSolve(self):
        for patchNormalTransfField in self.lsp.patchNormalTransfFields:
            self._patch2cell(patchNormalTransfField, timesRange=[self._step, self._step + 1])