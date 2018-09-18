#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=GPU-small
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=7
#SBATCH --gres=gpu:p100:1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

source /etc/profile.d/modules.sh
module load singularity

rm -f test-results-gpu.out

mpirun -n 1 singularity exec --nv software.simg python3 serial-gpu.py
