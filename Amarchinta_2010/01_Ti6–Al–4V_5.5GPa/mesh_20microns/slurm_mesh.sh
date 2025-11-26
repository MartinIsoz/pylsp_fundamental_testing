#!/bin/bash

# Name of the job
#SBATCH -J shm
#SBATCH -e shm.err
#SBATCH -o shm.out

# Partition to use
##SBATCH -p express
#SBATCH -p short

# Time limit
#SBATCH --time=0-02:00:0

# Number of processes
#SBATCH -n 32
#SBATCH --mem=240GB
##SBATCH --nodelist=kraken-m2
#SBATCH -N 1

# load openfoam
module load openfoam/2312

function run_and_log(){
  # Run a command and redirect it's output to a log file.
  # First argument is the program name (log file name),
  # rest of the arguments contain the string to run the program.

  cmd=$1
  run_commands="${@:2}"
  echo "Running $cmd with command: $run_commands"
  $run_commands &> log."$cmd"
  if [ $? -ne 0 ]; then
    echo "Running $cmd failed, see log."$cmd". Exiting."
    exit 1
  fi
}

run_and_log blockMesh blockMesh

run_and_log decomposePar_mesh decomposePar -force

run_and_log snappyHexMesh srun snappyHexMesh -overwrite -parallel

run_and_log renumberMesh_po_snappy srun renumberMesh -overwrite -parallel

run_and_log checkMesh srun checkMesh -constant -parallel

run_and_log reconstructParMesh reconstructParMesh -constant

# clean up after parellel mesh generation
case_dir="$(pwd)"

rm -rf $case_dir/[0-9]*
rm -rf $case_dir/processor*
rm -rf $case_dir/dynamicCode

rm -rf $case_dir/constant/polyMesh/cellZones                            #to switch-off subproblem definition

echo "Run done!"
