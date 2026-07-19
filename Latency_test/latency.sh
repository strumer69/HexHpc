#!/bin/bash
#SBATCH --partition=cpu-xeon-ib56
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --nodelist=ant10,ant11
#SBATCH --time=00:05:00
#SBATCH --job-name=latency

module purge  # unload all modules
module load gnu15/15.2.0 openmpi5/5.0.10

mpirun --map-by ppr:1:node ./latency