#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=gpu-shared
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=6
#SBATCH --gres=gpu:1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

module load singularity
module unload mvapich2_ib
module load openmpi_ib

rm -f test-results-gpu.out

ibrun -n 1 singularity exec --nv software.sif python3 serial-gpu.py

