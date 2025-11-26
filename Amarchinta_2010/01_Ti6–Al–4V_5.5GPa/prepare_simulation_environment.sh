#!/bin/bash
# -*- coding: utf-8 -*-

#  
#  name: prepare_simulation_environment
#  
#  function: prepares simulation environment on the current machine
#
#  new_install flag is to indicate that no pylsp environment is present
#  in the current working folder
#
#  recompile_foam flag is to indicate whether the foam part of pylsp
#  package should be recompiled
#  


#  prepare_simulation_environment.sh
#  
#  Copyright 2025 Martin Isoz <isozm>
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

# -- inputs ------------------------------------------------------------
# -- mandatory script settings
new_install=1                                                           #is this completely new?
reinstall_pylsp=1                                                       #if I want to reinstall pylsp
recompile_foam=1                                                        #update foam compilation
update_local_foam=1                                                     #replace the existing foam packages with updated ones
runs_on_kraken=1                                                        #do we work on kraken?

# -- auxilary script settings (to be modified for each local machine)
# --- path to openfoam installation for CMakeLists.txt
path_to_foam_dir=/usr/lib/openfoam/openfoam2312
# --- path to solids4foam installation for CMakeLists.txt
path_to_s4f_dir=/home/prado/solids4foam
# --- path to solids4foam library directory for CMakeLists.txt
path_to_s4f_lib=/usr/lib/openfoam/openfoam2312/platforms/linux64GccDPInt32Opt/lib

# -- initialize auxiliary variables
root_dir="$(pwd)"

# -- pylsp package installation part I ---------------------------------
# -- prepare the virtual environment
if [ "$new_install" -eq 1 ]; then
    echo "-- preparing new virtual environment in $root_dir"
    if [ "$runs_on_kraken" -eq 1 ]; then
       module purge
       ml python
    fi
    rm -rf .pylsp
    python3 -m venv .pylsp
    source .pylsp/bin/activate
    python -m pip install --upgrade pip
    python -m pip install numpy
    python -m pip install wheel
    python -m pip install ./AA_sof_pylsp --upgrade --force-reinstall 
    deactivate
    echo "-- prepared new virtual environment in $root_dir"
fi

# -- pylsp package installation part II --------------------------------
if [ "$reinstall_pylsp" -eq 1 ]; then
    echo "-- installing pylsp package"
    if [ "$runs_on_kraken" -eq 1 ]; then
       module purge
       ml python
    fi
    python3 -m venv .pylsp
    source .pylsp/bin/activate
    python -m pip install --upgrade pip
    python -m pip install numpy
    python -m pip install wheel
    python -m pip install ./AA_sof_pylsp --upgrade --force-reinstall 
    echo "-- installed pylsp package"
    # -- deactivate the virtual environment
    deactivate
fi

# -- lspfoam compilations ----------------------------------------------
if [ "$recompile_foam" -eq 1 ]; then
    echo "-- recompiling foam source codes"
    if [ "$runs_on_kraken" -eq 1 ]; then
        sed -i 's|^set(MACHINE ".*")$|set(MACHINE "KRAKEN")|' ./AA_sof_pylsp/foam/CMakeLists.txt
        module purge
        ml cmake
        ml gcc/13.3.0
    else
        cp ./AA_sof_pylsp/foam/CMakeLists.txt ./AA_sof_pylsp/foam/CMakeLists.txt.bac
        sed -i 's|^set(MACHINE ".*")$|set(MACHINE "LOCAL")|' ./AA_sof_pylsp/foam/CMakeLists.txt 
        sed -i "s|^    set(foam_com_DIR REPLACE_THIS)$|    set(foam_com_DIR $path_to_foam_dir)|" ./AA_sof_pylsp/foam/CMakeLists.txt 
        sed -i "s|^    set(solids4foam_DIR REPLACE_THIS)$|    set(solids4foam_DIR $path_to_s4f_dir)|" ./AA_sof_pylsp/foam/CMakeLists.txt 
        sed -i "s|^    set(solids4foam_LIB REPLACE_THIS)$|    set(solids4foam_LIB $path_to_s4f_lib)|" ./AA_sof_pylsp/foam/CMakeLists.txt
        cp ./AA_sof_pylsp/foam/CMakeLists.txt ./AA_sof_pylsp/foam/CMakeLists.txt.used
    fi
    cd ./AA_sof_pylsp/foam/
    rm -rf build
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release > log.cmake 2>&1
    cd build
    make > ../log.make 2>&1
    cd $root_dir
    if [ "$runs_on_kraken" -eq 0 ]; then
        cp AA_sof_pylsp/foam/CMakeLists.txt.bac ./AA_sof_pylsp/foam/CMakeLists.txt
        rm -f ./AA_sof_pylsp/foam/CMakeLists.txt.bac
    fi
    echo "-- recompiled foam source codes"
fi

# -- updating lspfoam binaries in current installation -----------------
if [ "$update_local_foam" -eq 1 ]; then
    if [ "$runs_on_kraken" -eq 1 ]; then
        module purge
        ml python
    fi
    python_version=$(python3 -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')")
    src="./AA_sof_pylsp/foam/build"
    dst="./.pylsp/lib/python$python_version/site-packages/lspfoam"
    for f in "$src"/*; do
        if [ -f "$f" ] && file "$f" | grep -qE 'executable|ELF'; then
            echo "---- updating $f"
            cp -f "$f" "$dst"/
        fi
    done
    if [ "$runs_on_kraken" -eq 1 ]; then
        module purge
    fi
    echo "-- updated local lsp binaries"
fi

echo "== environment preparation complete -> END"
