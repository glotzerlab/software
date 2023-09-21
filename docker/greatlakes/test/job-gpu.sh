#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=gpu
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --gres=gpu:1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

export PMIX_MCA_psec=^munge

module load gcc/10.3.0 openmpi/4.1.6 singularity

set -x
cd $SLURM_SUBMIT_DIR

mpirun -n 1 singularity exec --bind /scratch,/gpfs --nv software.sif python3 serial-gpu.py

echo "Tests complete."
