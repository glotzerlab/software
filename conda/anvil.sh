#!/bin/bash

#SBATCH --job-name="glotzerlab-software build"
#SBATCH --account=dmr140129
#SBATCH --partition=shared
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=32
#SBATCH --time=8:00:00

# Load modules used to build packages with native MPI support (no CUDA).
module reset
module load gcc/11.2.0 openmpi/4.1.6

export TMPDIR=/tmp

./build.sh "$@" \
    --skip-existing \
    --variants "{'cluster': ['anvil'], 'device': ['cpu']}" \
    --output-folder $PROJECT/software/conda

