#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=gpu
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --gres=gpu:1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

module load gcc/8.2.0 openmpi/4.0.2 singularity

rm -f test-results-gpu.out

mpirun -n 1 singularity exec --nv software.sif python3 serial-gpu.py
