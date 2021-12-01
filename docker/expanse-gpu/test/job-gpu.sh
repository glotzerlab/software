#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=gpu-shared
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --gpus=1
#SBATCH -t 0:10:00

module load gpu singularitypro openmpi/4.0.4

rm -f test-results-gpu.out

singularity exec --nv software.sif python3 serial-gpu.py
