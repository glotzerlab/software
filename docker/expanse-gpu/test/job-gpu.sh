#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=gpu-shared
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --gpus-per-task=1
#SBATCH -t 0:10:00

module load gpu singularitypro openmpi/4.0.4-nocuda

rm -f test-results-gpu.out

mpirun -n 1 singularity exec --nv software.sif python3 serial-gpu.py

mpirun -n 2 singularity exec --nv software.sif python3 mpi-gpu.py
