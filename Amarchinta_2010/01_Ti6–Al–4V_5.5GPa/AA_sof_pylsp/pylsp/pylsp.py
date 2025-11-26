from os import path, makedirs
from math import log
from sys import argv
from shutil import copyfile
from pylsp.utils import infoRawH2, infoRawH3, infoRawC2, infoLine2
from pylsp.case.relax.relax import Relax
from pylsp.case.trans.trans import Trans
from pylsp.case.draft.draft import Draft
from pylsp.case.loadCase.loadCase import LoadCase


class Point:
    def __init__(self, *, x=None, y=None, z=0.0):
        if isinstance(x, float):
            self._x = x
        else:
            raise TypeError ('Point.x has to be instance of float')

        if isinstance(y, float):
            self._y = y
        else:
            raise TypeError ('Point.y has to be instance of float')

        if isinstance(z, float):
            self._z = z
        else:
            raise TypeError ('Point.z has to be instance of float')

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    @property
    def z(self):
        return self._z


class LaserTimeProfile:
    def __init__(self, *, time=None, pressure=None):
        if isinstance(time, list):
            self._time = time
        else:
            raise TypeError('LaserTimeProfile.time has to be list')

        if isinstance(pressure, list):
            self._pressure = list(pressure)
        else:
            raise TypeError('LaserTimeProfile.pressure has to be list')

    @property
    def time(self):
        return self._time

    @property
    def pressure(self):
        return self._pressure


class LaserSpaceProfile:
    def __init__(self, *, radius=None, considerFaceNormal=False, square=[0.0, 0.0, 0.0]):
        self._radius = radius
        self._considerFaceNormal = considerFaceNormal
        self._square = square

    @property
    def radius(self):
        return self._radius

    @property
    def considerFaceNormal(self):
        return self._considerFaceNormal

    @property
    def square(self):
        return self._square


class PiecewiseLinearLaserSpaceProfile(LaserSpaceProfile):
    def __init__(self, *, radius=None, mult=None, square=[0.0, 0.0, 0.0], pureSquareRadius = 1e12, considerFaceNormal=False):
        super().__init__(radius=radius, square=square, considerFaceNormal=considerFaceNormal)

        if not isinstance(radius, list):
            raise TypeError('PiecewiseLinearLaserSpaceProfile.radius has to be list')

        if isinstance(mult, list):
            self._mult = list(mult)
        else:
            raise TypeError('PiecewiseLinearLaserSpaceProfile.mult has to be list')

        self._pureSquareRadius = pureSquareRadius

    @property
    def mult(self):
        return self._mult

    @property
    def pureSquareRadius(self):
        return self._pureSquareRadius


class ExponentialLaserSpaceProfile(LaserSpaceProfile):
    def __init__(self, *, radius=None, square=[0.0, 0.0, 0.0], a=None, c=None, n=None, modified=None, considerFaceNormal=False):
        super().__init__(radius=radius, square=square, considerFaceNormal=considerFaceNormal)

        if not isinstance(radius, float):
            raise TypeError('ExponentialLaserSpaceProfile.radius has to be float')

        if isinstance(a, float):
            self._a = float(a)
        else:
            raise TypeError('ExponentialLaserSpaceProfile.a has to be float')

        if isinstance(c, float):
            self._c = float(c)
        else:
            raise TypeError('ExponentialLaserSpaceProfile.c has to be float')

        if isinstance(n, int):
            self._n = float(n)
        else:
            raise TypeError('ExponentialLaserSpaceProfile.n has to be integer')

        if isinstance(modified, bool):
            self._modified = bool(modified)
        else:
            raise TypeError('ExponentialLaserSpaceProfile.modified has to be bool')

    @property
    def a(self):
        return self._a

    @property
    def c(self):
        return self._c

    @property
    def n(self):
        return self._n

    @property
    def modified(self):
        return self._modified


class LaserBeam:
    def __init__(self, *, startPoint=None, endPoint=None, timeProfile=None, spaceProfile=None):
        if isinstance(startPoint, Point):
            self._startPoint = startPoint
        else:
            raise TypeError ('LaserBeam.startPoint has to be instance of Point')

        if isinstance(endPoint, Point):
            self._endPoint = endPoint
        else:
            raise TypeError ('LaserBeam.endPoint has to be instance of Point')

        if isinstance(timeProfile, LaserTimeProfile):
            self._timeProfile = timeProfile
        else:
            raise TypeError ('LaserBeam.timeProfile has to be instance of LaserTimeProfile')

        if isinstance(spaceProfile, LaserSpaceProfile):
            self._spaceProfile = spaceProfile
        else:
            raise TypeError ('LaserBeam.spaceProfile has to be instance of LaserSpaceProfile')

    @property
    def startPoint(self):
        return self._startPoint

    @property
    def endPoint(self):
        return self._endPoint

    @property
    def timeProfile(self):
        return self._timeProfile

    @property
    def spaceProfile(self):
        return self._spaceProfile

class System:
    def __init__(self, *, foam_org=None, foam_com=None, foam_extend=None, MPI='mpirun'):
        self._foam_org = foam_org
        self._foam_com = foam_com
        self._foam_extend = foam_extend
        self._MPI = MPI # 'mpirun' for spejbl | 'srun' for kraken

    @property
    def foam_org(self):
        return self._foam_org

    @property
    def foam_com(self):
        return self._foam_com

    @property
    def foam_extend(self):
        return self._foam_extend

    @property
    def MPI(self):
        return self._MPI

class TransientAnalysis:
    def __init__(self, *, endTime=None, maxCo=None, writeInterval=None):
        self._endTime = float(endTime)
        self._maxCo = float(maxCo)
        self._writeInterval = float(writeInterval)

    @property
    def endTime(self):
        return self._endTime

    @property
    def maxCo(self):
        return self._maxCo

    @property
    def writeInterval(self):
        return self._writeInterval


class Material:
    def __init__(self, *, rho=None, E=None, nu=None):
        self._rho = float(rho)
        self._E = float(E)
        self._nu = float(nu)

    @property
    def rho(self):
        return self._rho

    @property
    def E(self):
        return self._E

    @property
    def nu(self):
        return self._nu


class LinearElasticMaterial(Material):
    def __init__(self, *, rho=None, E=None, nu=None):
        super().__init__(rho=rho, E=E, nu=nu)


class MisesIdealPlasticsMaterial(Material):
    def __init__(self, *, rho=None, E=None, nu=None, fy=None):
        super().__init__(rho=rho, E=E, nu=nu)

        if isinstance(fy, float):
            self._fy = float(fy)
        else:
            raise TypeError('MisesIdealPlasticsMaterial.fy has to be float')

    def yieldStress(self, *, epsP=0, epsPdot=0):
        return self.fy

    @property
    def fy(self):
        return self._fy


class JohnsonCookPlasticsMaterial(Material):
    def __init__(self, *, rho=None, E=None, nu=None, A=None, B=None, C=None, n=None, epsDot0=None):
        super().__init__(rho=rho, E=E, nu=nu)

        if isinstance(A, float):
            self._A = float(A)
        else:
            raise TypeError('JohnsonCookPlasticsMaterial.A has to be float')

        if isinstance(B, float):
            self._B = float(B)
        else:
            raise TypeError('JohnsonCookPlasticsMaterial.B has to be float')

        if isinstance(C, float):
            self._C = float(C)
        else:
            raise TypeError('JohnsonCookPlasticsMaterial.C has to be float')

        if isinstance(n, float):
            self._n = float(n)
        else:
            raise TypeError('JohnsonCookPlasticsMaterial.n has to be float')

        if isinstance(epsDot0, float):
            self._epsDot0 = float(epsDot0)
        else:
            raise TypeError('JohnsonCookPlasticsMaterial.epsDot0 has to be float')

    def yieldStress(self, *, epsP=0, epsPdot=0):
        answ = self._A + self._B * pow(epsP, self._n)
        answ *= (1.0 + self._C * log(max(1.0, epsPdot / self._epsDot0)))
        return answ

    @property
    def A(self):
        return self._A

    @property
    def B(self):
        return self._B

    @property
    def C(self):
        return self._C

    @property
    def n(self):
        return self._n

    @property
    def epsDot0(self):
        return self._epsDot0


class LimHuhPlasticsMaterial(Material):
    def __init__(self, *, rho=None, E=None, nu=None, K=None, eps0=None, n=None, q1=None, q2=None, q3=None, p=None, epsDot0=None):
        super().__init__(rho=rho, E=E, nu=nu)

        if isinstance(K, float):
            self._K = float(K)
        else:
            raise TypeError('LimHuhPlasticsMaterial.K has to be float')

        if isinstance(eps0, float):
            self._eps0 = float(eps0)
        else:
            raise TypeError('LimHuhPlasticsMaterial.eps0 has to be float')

        if isinstance(n, float):
            self._n = float(n)
        else:
            raise TypeError('LimHuhPlasticsMaterial.n has to be float')

        if isinstance(q1, float):
            self._q1 = float(q1)
        else:
            raise TypeError('LimHuhPlasticsMaterial.q1 has to be float')

        if isinstance(q2, float):
            self._q2 = float(q2)
        else:
            raise TypeError('LimHuhPlasticsMaterial.q2 has to be float')

        if isinstance(q3, float):
            self._q3 = float(q3)
        else:
            raise TypeError('LimHuhPlasticsMaterial.q3 has to be float')

        if isinstance(p, float):
            self._p = float(p)
        else:
            raise TypeError('LimHuhPlasticsMaterial.p has to be float')

        if isinstance(epsDot0, float):
            self._epsDot0 = float(epsDot0)
        else:
            raise TypeError('LimHuhPlasticsMaterial.epsDot0 has to be float')

    def yieldStress(self, *, epsP=0, epsPdot=0):
        answ = self._K * pow(epsP + self._eps0, self._n)
        q = self._q1 / pow(epsP + self._q2, self._q3)
        answ *= (1.0 + q * pow(epsPdot, self._p)) / (1.0 + q * pow(self._epsDot0, self._p))
        return answ

    @property
    def K(self):
        return self._K

    @property
    def eps0(self):
        return self._eps0

    @property
    def n(self):
        return self._n

    @property
    def q1(self):
        return self._q1

    @property
    def q2(self):
        return self._q2

    @property
    def q3(self):
        return self._q3

    @property
    def p(self):
        return self._p

    @property
    def epsDot0(self):
        return self._epsDot0


class FvSchemes:
    def __init__(self, *, gradSchemes=None, divSchemes=None, laplacianSchemes=None, snGradSchemes=None, interpolationSchemes=None):
        self._gradSchemes = str(gradSchemes)
        self._divSchemes = str(divSchemes)
        self._laplacianSchemes = str(laplacianSchemes)
        self._snGradSchemes = str(snGradSchemes)
        self._interpolationSchemes = str(interpolationSchemes)

    @property
    def gradSchemes(self):
        return self._gradSchemes

    @property
    def divSchemes(self):
        return self._divSchemes

    @property
    def laplacianSchemes(self):
        return self._laplacianSchemes

    @property
    def snGradSchemes(self):
        return self._snGradSchemes

    @property
    def interpolationSchemes(self):
        return self._interpolationSchemes

# class FvSolution:
#     def __init__(self, *, solver=None, preconditioner=None, tolerance=None, relTol=None):
#         self._solver = str(solver)
#         self._preconditioner = str(preconditioner)
#         self._tolerance = float(tolerance)
#         self._relTol = float(relTol)
#
#     @property
#     def solver(self):
#         return self._solver
#
#     @property
#     def preconditioner(self):
#         return self._preconditioner
#
#     @property
#     def tolerance(self):
#         return self._tolerance
#
#     @property
#     def relTol(self):
#         return self._relTol

class FvSolution:
    def __init__(self, *, solver=None, preconditioner=None, tolerance=None, relTol=None, agglomerator='faceAreaPair', mergeLevels=1, cacheAgglomeration='true', nCellsInCoarsestLevel=200, smoother='GaussSeidel', nPreSweeps=0, nPostSweeps=2, nFinestSweeps=2, minIter=1):

        self._solver = str(solver)
        self._preconditioner = str(preconditioner)
        self._tolerance = float(tolerance)
        self._relTol = float(relTol)

        self._agglomerator = str(agglomerator)
        self._mergeLevels  = int(mergeLevels)
        self._cacheAgglomeration = str(cacheAgglomeration)
        self._nCellsInCoarsestLevel = int(nCellsInCoarsestLevel)
        self._smoother      = str(smoother)
        self._nPreSweeps    = int(nPreSweeps)
        self._nPostSweeps   = int(nPostSweeps)
        self._nFinestSweeps = int(nFinestSweeps)
        self._minIter       = int(minIter)

    @property
    def solver(self):
        return self._solver

    @property
    def preconditioner(self):
        return self._preconditioner

    @property
    def tolerance(self):
        return self._tolerance

    @property
    def relTol(self):
        return self._relTol

    @property
    def agglomerator(self):
        return self._agglomerator

    @property
    def mergeLevels(self):
        return self._mergeLevels

    @property
    def cacheAgglomeration(self):
        return self._cacheAgglomeration

    @property
    def nCellsInCoarsestLevel(self):
        return self._nCellsInCoarsestLevel

    @property
    def smoother(self):
        return self._smoother

    @property
    def nPreSweeps(self):
        return self._nPreSweeps

    @property
    def nPostSweeps(self):
        return self._nPostSweeps

    @property
    def nFinestSweeps(self):
        return self._nFinestSweeps

    @property
    def minIter(self):
        return self._minIter


class LSP:
    def __init__(self, *, numberOfProcessors=1, meshCase=None, BCfile=None, system=None, material=None, laserBeams=None, transientAnalysis=None, fvSchemes=None, fvSolution=None, writeFields=['D', 'epsilon', 'epsilonEq', 'epsilonf', 'epsilonP', 'epsilonPEq', 'epsilonPEqf', 'epsilonPf', 'sigma', 'sigmaEq', 'sigmaf', 'sigmaHyd', 'sigmaHydf'], solverDirAppendix='', patchNormalTransfFields =[]):
        self.__version__ = '0.4.1'
        self._writeFields = writeFields
        self._numberOfProcessors = numberOfProcessors
        self._BCfile = BCfile
        self._meshCase = meshCase
        self._unstructuredApproach = False
        self._solverDirAppendix = solverDirAppendix
        self._patchNormalTransfFields = patchNormalTransfFields

        if isinstance(system, System):
            self._system = system
        else:
            raise TypeError('LSP.system has to be instance of System')

        if isinstance(material, LinearElasticMaterial) \
                or isinstance(material, MisesIdealPlasticsMaterial) \
                or isinstance(material, JohnsonCookPlasticsMaterial) \
                or isinstance(material, LimHuhPlasticsMaterial):
            self._material = material
        else:
            raise TypeError('LSP.material has to be instance of \
                            LinearElasticMaterial,\
                            MisesIdealPlasticsMaterial,\
                            JohnsonCookPlasticsMaterial,\
                            or LimHuhPlasticsMaterial')

        self._laserBeams = []
        for laserBeam in laserBeams:
            if isinstance(laserBeam, LaserBeam):
                self._laserBeams.append(laserBeam)
            else:
                raise TypeError('LSP.laserBeam has to be instance of LaserBeam')

        if isinstance(transientAnalysis, TransientAnalysis):
            self._transientAnalysis = transientAnalysis
        else:
            raise TypeError('LSP.transientAnalysis has to be instance of TransientAnalysis')

        if isinstance(fvSchemes, FvSchemes):
            self._fvSchemes = fvSchemes
        else:
            raise TypeError('LSP.fvSchemes has to be instance of FvSchemes')

        if isinstance(fvSolution, FvSolution):
            self._fvSolution = fvSolution
        else:
            raise TypeError('LSP.fvSolution has to be instance of FvSolution')

    def _testSolverDirExists(self, solverDir):
        if path.exists(solverDir):
            infoRawH2('ANALYSIS', 'error')
            infoRawC2('solver directory exists', solverDir)
            infoRawC2('', '')
            infoRawC2('', 'move or delete the folder before new simulation')
            infoLine2()
            print()
            infoRawH3('LSP SIMUL', self.__version__, 'END', bold=True, newLine=True)
            exit()

    def _infoBasicCaseInfo(self, SIMUL_DIR, startStep, endStep):
        infoRawH2('ANALYSIS', 'info')
        infoRawC2('simul dir', SIMUL_DIR)
        infoRawC2('mesh case', self._meshCase)
        infoRawC2('BCs file', self._BCfile)
        infoLine2()
        infoRawC2('processors', str(self._numberOfProcessors))
        infoRawC2('first analysis step', str(startStep))
        infoRawC2('last analysis step', str(endStep))
        infoLine2()
        print()

    @property
    def patchNormalTransfFields(self):
        return self._patchNormalTransfFields

    @property
    def writeFields(self):
        return self._writeFields

    @property
    def numberOfProcessors(self):
        return self._numberOfProcessors

    @property
    def meshCase(self):
        return self._meshCase

    @property
    def BCfile(self):
        return self._BCfile

    @property
    def unstructuredApproach(self):
        return self._unstructuredApproach

    @property
    def system(self):
        return self._system

    @property
    def material(self):
        return self._material

    @property
    def laserBeams(self):
        return self._laserBeams

    @property
    def transientAnalysis(self):
        return self._transientAnalysis

    @property
    def fvSchemes(self):
        return self._fvSchemes

    @property
    def fvSolution(self):
        return self._fvSolution

    def simul(self, *, startStep=0):
        endStep = len(self._laserBeams) - 1
        simulationScriptBaseName = path.basename(argv[0])
        simulationScriptDir = path.abspath(path.dirname(argv[0]))
        solverDir = path.join(simulationScriptDir, 'solver_' + simulationScriptBaseName.split('.')[0] + self._solverDirAppendix)

        print()
        infoRawH3('LSP SIMUL', self.__version__, 'START', bold=True, newLine=True)
        self._testSolverDirExists(path.join(solverDir, 'RELAX'))
        self._testSolverDirExists(path.join(solverDir, 'TRANS'))
        try:
            makedirs(solverDir)
        except:
            pass
        copyfile(path.join(simulationScriptDir, simulationScriptBaseName), path.join(solverDir, simulationScriptBaseName))
        self._infoBasicCaseInfo(solverDir, startStep, endStep)

        relax = Relax(solverDir, self)
        trans = Trans(solverDir, self)


        for step in range(startStep, endStep + 1):
            infoRawH3('ANALYSIS', 'start step = ' + str(step), 'end step = ' + str(endStep), bold=True, newLine=True)

            trans.solve(step)
            relax.solve(step)
            infoRawH3('ANALYSIS', 'FINISH', str(step) + ' / ' + str(endStep), newLine=True)

        infoRawH3('LSP SIMUL', self.__version__, 'END', bold=True, newLine=True)

    def simulLC(self, *, startStep, BCfile):
        endStep = startStep + 1
        simulationScriptBaseName = path.basename(argv[0])
        simulationScriptDir = path.abspath(path.dirname(argv[0]))
        lspSolverDir = path.join(simulationScriptDir, 'solver_' + simulationScriptBaseName.split('.')[0] + self._solverDirAppendix)
        name = path.basename(BCfile)
        solverDir = path.join(lspSolverDir, name, str(startStep))

        print()
        infoRawH3('LSP LOAD CASE: ' + name + '/' + str(startStep), self.__version__, 'START', bold=True, newLine=True)
        self._testSolverDirExists(solverDir)
        makedirs(solverDir)
        copyfile(path.join(simulationScriptDir, simulationScriptBaseName), path.join(solverDir, simulationScriptBaseName))
        self._BCfile = BCfile
        self._infoBasicCaseInfo(solverDir, startStep, endStep)

        loadCase = LoadCase(lspSolverDir, solverDir, self, startStep, name)

        infoRawH3('ANALYSIS', 'start step = ' + str(startStep), 'end step = ' + str(endStep), bold=True, newLine=True)

        loadCase.solve()
        infoRawH3('ANALYSIS', 'FINISH', str(startStep) + ' / ' + str(endStep), newLine=True)

        infoRawH3('LSP LOAD CASE', self.__version__, 'END', bold=True, newLine=True)

    def draft(self, meshCase, *, startStep=0):
        endStep = len(self._laserBeams) - 1
        simulationScriptBaseName = path.basename(argv[0])
        simulationScriptDir = path.abspath(path.dirname(argv[0]))
        solverDir = path.join(simulationScriptDir, 'solver_' + simulationScriptBaseName.split('.')[0] + self._solverDirAppendix)

        print()
        infoRawH3('LSP DRAFT', self.__version__, 'START', bold=True, newLine=True)
        self._testSolverDirExists(path.join(solverDir, 'DRAFT'))
        makedirs(path.join(solverDir, 'DRAFT'))
        copyfile(path.join(simulationScriptDir, simulationScriptBaseName), path.join(solverDir, simulationScriptBaseName))
        self._infoBasicCaseInfo(solverDir, startStep, endStep)

        draft = Draft(solverDir, self, meshCase)

        for step in range(startStep, endStep + 1):
            infoRawH3('ANALYSIS', 'start step = ' + str(step), 'end step = ' + str(endStep), bold=True, newLine=True)

            draft.solve(step)

            infoRawH3('ANALYSIS', 'FINISH', str(step) + ' / ' + str(endStep), newLine=True)


        infoRawH3('LSP DRAFT', self.__version__, 'END', bold=True, newLine=True)


if __name__ == "__main__":
    pass
