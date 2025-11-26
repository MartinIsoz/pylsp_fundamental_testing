#!/bin/bash

# Name of the job
#SBATCH -J Amar_5.5GPa
#SBATCH -e lsp.err
#SBATCH -o lsp.out

# Partition to use
##SBATCH -p express
#SBATCH -p short

# Time limit
#SBATCH --time=2-00:00:0

# Number of processes
#SBATCH -n 32
#SBATCH --mem=240GB
##SBATCH --nodelist=kraken-m2
#SBATCH --exclude=kraken-l[1-4]
#SBATCH -N 1

source .pylsp/bin/activate
python3 run_simulation.py >> log.lsp

echo "Run done!"
