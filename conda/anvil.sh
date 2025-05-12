#!/bin/bash

#SBATCH --job-name="glotzerlab-software build"
#SBATCH --account=dmr140129
#SBATCH --partition=shared
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=32
#SBATCH --time=8:00:00

export OUTPUT_FOLDER=$PROJECT/software/conda
unset CMAKE_PREFIX_PATH

# Work around Purdue network dropping traffic to conda package servers.
export HTTPS_PROXY=squid.rcac.purdue.edu:3128

# Load modules used to build packages with native MPI support (no CUDA).
module reset
module load gcc/11.2.0 openmpi/4.1.6

export CC=$GCC_HOME/bin/gcc
export CXX=$GCC_HOME/bin/g++

./build.sh "$@" \
    --skip-existing \
    --variants "{'cluster': ['anvil'], 'device': ['cpu'], 'gpu_platform': ['none']}" \
    --output-folder $OUTPUT_FOLDER

chmod g-w $OUTPUT_FOLDER -R
