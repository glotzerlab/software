#!/bin/bash

#SBATCH --job-name="glotzerlab-software build"
#SBATCH --account=bbgw-delta-gpu
#SBATCH --partition=gpuA40x4
#SBATCH --nodes=1
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=16
#SBATCH --mem=48g
#SBATCH --gpus=1
#SBATCH --time=8:00:00

# TODO: rewrite to use CPU account when it is renewed
export OUTPUT_FOLDER=/projects/bbgw/software/conda

# Load modules used to build packages with native MPI and CUDA support.
module reset
module load gcc/11.4.0 openmpi/4.1.6 cuda/12.3.0

./build.sh "$@" \
    --skip-existing \
    --variants "{'cluster': ['delta'], 'device': ['gpu'], 'gpu_platform': ['CUDA']}" \
    --output-folder $OUTPUT_FOLDER

chmod g-w $OUTPUT_FOLDER -R
chmod g+rX $OUTPUT_FOLDER -R
