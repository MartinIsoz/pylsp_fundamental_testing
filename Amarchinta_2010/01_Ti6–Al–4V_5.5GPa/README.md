# Repository.

This case is oriented to reproduce Amarchinta_2010 paper results for Ti6–Al–4V alloy. 
    REF: Amarchinta, H. K., Grandhi, R. V., Clauer, A. H., Langer, K., & Stargel, D. S.       (2010). Simulation of residual stress induced by a laser peening process through inverse optimization of material models. Journal of Materials Processing Technology, 210(14), 1997-2006.

## repository structure:

### ./

run_simulation.py  
-> main script to run the simulation

que_job_on_slurm_cluster.sh  
-> bash script that will prepare environment for run_simulation.py queuing on slurm cluster and run the script

prepare_simulation_environment.sh  
-> bash script that will prepare the envirohment for running the study  
-> !! before submitting large scale jobs on kraken, always make sure you have up-to-date environment  
-> script allows for  
- initial installation of pylsp python package, including virtual environment creation  
- compilation of foam source codes  
    - !! if you run this on local machine, it requires correct path settings to foam installations on the system
- installation/upgrade of pylsp python package  

### ./BB_laser_props/

laser_characterization.py  
-> python module to provide temporal pressure profile accordingly to Amarchinta_2010.

### ./mesh_boundary_conditions/

D
-> openFoam file for displacements - setting boundary conditions for the RELAX solver

### ./mesh_40microns/

Folder with prepared mesh of cellSize = 40microns
    - !!To create new mesh resolutions, copy this folder and rename it as "mesh_XXXmicrons", being XXX the desired mesh size. Then, in     ./mesh_40microns/system/, edit file meshGenerationSettings and select the value of "target_cell_size" variable in meters. Lastly, in "run_simulation.py", change "mesh_dir     = "./mesh_40microns/"" to the desired folder with the mesh contained.

./mesh_40microns/clean_mesh.sh  
-> cleans the mesh folder

./mesh_40microns/local_mesh.sh  
-> prepared for mesh generation on local machine

./mesh_40microns/slurm_mesh.sh  
-> prepared for mesh generation on slurm cluster

### ./mesh_20microns/

Folder with prepared mesh of cellSize = 20microns
    - !!To create new mesh resolutions, copy this folder and rename it as "mesh_XXXmicrons", being XXX the desired mesh size. Then, in     ./mesh_40microns/system/, edit file meshGenerationSettings and select the value of "target_cell_size" variable in meters. Lastly, in "run_simulation.py", change "mesh_dir     = "./mesh_40microns/"" to the desired folder with the mesh contained.

./mesh_20microns/clean_mesh.sh  
-> cleans the mesh folder

./mesh_20microns/local_mesh.sh  
-> prepared for mesh generation on local machine

./mesh_20microns/slurm_mesh.sh  
-> prepared for mesh generation on slurm cluster

### ./AA_sof_pylsp

folder with pylsp codes used to run the study
