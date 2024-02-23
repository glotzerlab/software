#!/bin/bash

# Load modules used to build packages with native MPI support (no CUDA).
module reset
module load gcc/11.2.0 openmpi/4.1.6

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
      --variants "{'cluster': ['anvil'], 'device': ['cpu']}" \
      --output-folder /anvil/projects/x-dmr140129/software/conda
