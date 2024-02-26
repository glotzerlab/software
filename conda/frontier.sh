#!/bin/bash

# Load modules used to build packages with native MPI and HIP support
module purge
module load PrgEnv-gnu rocm/5.4.3
module unload darshan-runtime

export OUTPUT_FOLDER=/ccs/proj/mat110/software/frontier/conda

# The cray-mpich module does not provide this, it is needed to build mpi4py from source.
export MPICC=$CRAY_MPICH_DIR/bin/mpicc
export CC=$GCC_PATH/bin/gcc
export CXX=$GCC_PATH/bin/g++
export HCC_AMDGPU_TARGET=gfx90a 

./build.sh "$@" \
    --skip-existing \
    --variants "{'cluster': ['frontier'], 'device': ['gpu'], 'gpu_platform': ['HIP']}" \
    --output-folder $OUTPUT_FOLDER

chmod g-w $OUTPUT_FOLDER -R

