#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=GPU-shared
#SBATCH --nodes=1
#SBATCH --gpus-per-node=1
#SBATCH -t 0:20:00

module load openmpi

rm -f test-results-gpu.out

mpirun -n 1 singularity exec --nv software.sif python3 serial-gpu.py
