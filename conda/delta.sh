#!/bin/bash

#SBATCH --job-name="glotzerlab-software build"
#SBATCH --account=bbgw-delta-cpu
#SBATCH --partition=cpu
#SBATCH --nodes=1
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=16
#SBATCH --mem-per-cpu=2000M
#SBATCH --time=8:00:00

export OUTPUT_FOLDER=/projects/bbgw/software/conda
unset CMAKE_PREFIX_PATH

# Load modules used to build packages with native MPI and CUDA support.
module reset

# Override compiler environment as PrgEnv-gnu fails to work correctly with CMake
export CC=/opt/rh/gcc-toolset-13/root/usr/bin/gcc
export CXX=/opt/rh/gcc-toolset-13/root/usr/bin/g++

export CMAKE_LIBRARY_PATH="/opt/nvidia/hpc_sdk/Linux_x86_64/25.3/math_libs/12.8/targets/x86_64-linux/lib:/opt/nvidia/hpc_sdk/Linux_x86_64/25.3/cuda/12.8/targets/x86_64-linux/lib"

./build.sh "$@" \
    --skip-existing \
    --variants "{'cluster': ['delta'], 'device': ['gpu'], 'gpu_platform': ['CUDA']}" \
    --output-folder $OUTPUT_FOLDER

chmod g-w $OUTPUT_FOLDER -R
chmod g+rX $OUTPUT_FOLDER -R
