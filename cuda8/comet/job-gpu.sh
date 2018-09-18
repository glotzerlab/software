#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=gpu-shared
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=6
#SBATCH --gres=gpu:1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

module load singularity

rm -f test-results-gpu.out

singularity exec --nv software.simg python3 serial-gpu.py

