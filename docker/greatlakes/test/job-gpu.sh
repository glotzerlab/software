#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=gpu
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --gres=gpu:1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

module load gcc/10.3.0 openmpi/4.1.4 singularity

set -x

mpirun -n 1 singularity exec --nv software.sif python3 serial-gpu.py

echo "Tests complete."
