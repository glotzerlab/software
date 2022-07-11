#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=gpuA100x4
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --gpus=1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

module load gcc/11.2.0 openmpi/4.1.2

rm -f test-results-gpu.out

mpirun -n 1 singularity exec --nv software.sif python3 serial-gpu.py
