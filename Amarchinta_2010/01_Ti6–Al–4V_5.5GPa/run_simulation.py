#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#FILE DESCRIPTION=======================================================
#
# script prepared for testing of a rounded edge geometry
#
# Three simulations are ran:
# a) a shot is placed directly on the edge
# b) a shot is placed 1r from the edge
# c) a shot is placed 2r from the edge
#
# To adapt the script for your mesh you need to:
# - provide a folder with mesh of given (testing) dimensions
#   width_depth_dp 3.6;                                                 //X, Z direction, in dp
#   length_dp 6;                                                        //Y direction, in dp
#   Note: the mesh should be oriented in a "standard" manner, the shots
#         are placed in the z = 0 surface
# - provide a folder with boundary conditions suitable for your mesh
# - adjust the number of cores and paths to programs installation
#   according to your machine (and your sbatch script if ran on kraken)
#

#LICENSE================================================================
#  rounded_mesh_testing.py
#
#  Copyright 2025 Martin Isoz <isozm>
#                 Pavel Kotalik <kotalik>
#                 Anna Kovarnova <kovarnoa>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#
#

#IMPORT BLOCK===========================================================
# -- standard python packages
from os import getcwd, path, makedirs, listdir, walk
from shutil import rmtree,copytree,copy2
from numpy import linspace
from math import ceil
import subprocess
import sys
import time
import os

# -- pyLSP related python packages
import pylsp
sys.path.insert(1, './BB_laser_props/')                                     #folder with auxiliary python codes
from laser_characterization import *

#CUSTOM FUNCTIONS=======================================================
def copy_tree(src, dst):
    """
    Recursively copy a directory tree from src to dst.
    Equivalent replacement for distutils.dir_util.copy_tree.
    """
    if not path.exists(dst):
        makedirs(dst)

    for item in listdir(src):
        s = path.join(src, item)
        d = path.join(dst, item)
        if path.isdir(s):
            copytree(s, d, dirs_exist_ok=True)
        else:
            copy2(s, d)

#SIMULATION SETTINGS====================================================
# -- laser settings
tau        = 10.0e-9                                                    #temporal pulse width (corresponds to Litron)
tau_p      = 10.0*tau                                                   #time during which the pulse/pressure loading is active
spot_type  = "circle"                                                   #basically a dummy to allow for simpler computations of area
laser_incl = 0.0                                                        #inclination of laser beam in DEGREES
# -- material settings
johnson_cook_plastic_material = pylsp.JohnsonCookPlasticsMaterial(
    rho = 4500e0,
    E   = 113.8e9,
    nu  = 0.33,
    A   = 950e6,
    B   = 603.28e6,
    C   = 0.0198,
    n   = 0.1992,
    epsDot0=9.32e-4
)
# -- domain settings
spot_rad     = 2.8*1e-3
# -- case settings
mesh_dir     = "./mesh_40microns/"                               #directory with prepared mesh
bc_dir       = "./mesh_boundary_conditions/"                         #directory with file D that contains boundary conditions
# -- computer settings
n_cores      = 8                                                        #how many cores will be used (sync this with slurm)
#foam_source  = 'source /lib/openfoam/openfoam2312/etc/bashrc'           #how to load openfoam -> local
#mpi_access   = 'mpirun'                                                 #parallel running -> local
foam_source  = 'module purge ; module load solids4foam'                 #how to load openfoam -> kraken
mpi_access   = 'srun'                                                   #parallel running -> kraken

#SCRIPT ITSELF==========================================================
# -- auxilary variables for runs
script_name  = path.basename(__file__).split(".py")[0]

# -- auxuliary variables for run analysis
start_time = time.time()

# -- prepare the time-evolution of LSP-induced pressure loading
T    = np.arange(0.0,tau_p,tau_p*2.0e-2)                        #temporal profile definition and resolution
P,_  = pTime(T)
P[-1]= 0.0                                                      #hardcoded to end with zero pressure
p0 = 5.5e9

laser_time_profile  = pylsp.LaserTimeProfile(
    time   = [val for val in T],
    pressure  = [val*p0 for val in P]
)

# -- prepare spatial evolution of LSP-induced pressure loading
laser_space_profile = pylsp.PiecewiseLinearLaserSpaceProfile(
    radius=[r*spot_rad for r in [0.0,0.2,0.6,0.8,1.0]],  # ahora en m
    mult=[0.82,0.85,1.0,1.0,0.0],
    square=[0.0,0.0,0.0],
    pureSquareRadius=1e12,
    considerFaceNormal=False
)

case_start_time = time.time()

mesh_name    = os.path.basename(os.path.normpath(mesh_dir))         # → 'mesh_XXmicrons'
resolution   = mesh_name.replace("mesh_", "")                       # → 'XXmicrons'
appendix     = f"_{resolution}"                                     #name the directory by case index
sim_dir      = "./solver_%s%s/"%(script_name,appendix)              #directory in which the LSP simulations will be ran

# -- remove the simulation directory to be able to re-run
if path.exists(sim_dir):
    rmtree(sim_dir)

laser_beams = []
laser_beams.append(
    pylsp.LaserBeam(
        startPoint=pylsp.Point(x=0., y=0., z=-1.),
        endPoint=pylsp.Point(x=0., y=0., z=1.),
        timeProfile=laser_time_profile,
        spaceProfile=laser_space_profile
    )
)

# -- construct LSP object
lsp = pylsp.LSP(
    numberOfProcessors=n_cores,
    meshCase=path.join(getcwd(), mesh_dir),
    BCfile=path.join(getcwd(), bc_dir, 'D'),
    writeFields=['sigma', 'sigmaEq', 'epsilonPEqDot', 'epsilonPEq', 'U'],  # ['D', 'epsilonP', 'epsilonPf'] are included in all cases
    solverDirAppendix=appendix,
    patchNormalTransfFields=['sigma', 'epsilonP'],

    # SYSTEM
    system=pylsp.System(
        foam_com=foam_source,
        MPI=mpi_access
    ),

    # MATERIAL
    material=johnson_cook_plastic_material,

    # LASER POSITIONS IN TIME
    laserBeams=laser_beams,

    # TRANSIENT ANALYSIS SETTING
    transientAnalysis=pylsp.TransientAnalysis(
        maxCo = 0.2,
        writeInterval = 10e-9,
        endTime = 600e-9
    ),

    # FV DISCRETIZATION SCHEMES USED FOR TRANSIENT AND RELAXATION ANALYSIS
    # Podle ortogonality site zmenit!
    fvSchemes=pylsp.FvSchemes(
        gradSchemes='default leastSquares',
        divSchemes='default Gauss linear',
        laplacianSchemes='default Gauss linear orthogonal', #skewCorrected 1',
        snGradSchemes='default orthogonal', # 'default skewCorrected 1',
        interpolationSchemes='default linear'
    ),

    # RELAXATION ANALYSIS SOLVER SETTINGS
    fvSolution=pylsp.FvSolution(
        solver='GAMG',
        preconditioner='FDIC',
        tolerance=1e-11,
        relTol=1e-01
    )
)

# -- run the simulation
lsp.simul()
#lsp.draft(lsp.meshCase)

# -- time measurement
case_end_time = time.time()
case_time     = case_end_time - case_start_time
print("\n==RUNTIME ANALYSIS==")
print("-- time per one case: %f s -> %f min -> %f hours."%(case_time,case_time/60.0,case_time/3600.0))

end_time = time.time()
execution_time = end_time - start_time
print("Running on %02d cores, program finished execution in %f s."%(n_cores,execution_time))
