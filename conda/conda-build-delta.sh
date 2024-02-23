#!/bin/bash

# Please use a compute node to build packages.
# salloc --account=bbgw-delta-gpu --partition=gpuA40x4 --nodes=1 --tasks=1 --tasks-per-node=1 --cpus-per-task=16 --mem=48g --gpus=1 --time 4:00:00

# Load modules used to build packages with native MPI and CUDA support.
module reset
module load gcc/11.4.0 openmpi/4.1.6 cuda/12.3.0

# Build package format 2
export CONDARC=.condarc

# Build on a node local SSD.
export CONDA_BLD_PATH=`mktemp --directory --tmpdir=/tmp conda-build-${USER}.XXXXXXXX`

function cleanup {
  rm -rf "$CONDA_BLD_PATH"
}

trap cleanup EXIT

conda build  "$@" \
      --skip-existing \
      --variants "{'cluster': ['delta'], 'device': ['gpu']}" \
      --output-folder /projects/bbgw/software/conda
