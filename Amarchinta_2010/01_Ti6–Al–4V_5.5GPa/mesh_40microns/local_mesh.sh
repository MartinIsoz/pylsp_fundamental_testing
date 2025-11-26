#!/bin/bash

# auxiliary function
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

# load openfoam
oFVersion=openfoam2312
source /usr/lib/openfoam/$oFVersion/etc/bashrc

nCores=8
sed -i "/^numberOfSubdomains/c\numberOfSubdomains    $nCores;" system/decomposeParDict

run_and_log blockMesh blockMesh

run_and_log decomposePar decomposePar -force

run_and_log snappyHexMesh mpirun -np $nCores snappyHexMesh -overwrite -parallel

run_and_log checkMesh mpirun -np $nCores checkMesh -constant -parallel

run_and_log reconstructParMesh reconstructParMesh -constant

# run_and_log topoSet_serial topoSet -constant

# clean up after parellel mesh generation
case_dir="$(pwd)"

rm -rf $case_dir/[0-9]*
rm -rf $case_dir/processor*
rm -rf $case_dir/dynamicCode

rm -rf $case_dir/constant/polyMesh/cellZones                            #to switch-off subproblem definition

echo "Run done!"
