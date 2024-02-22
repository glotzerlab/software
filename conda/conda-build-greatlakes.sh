#!/bin/bash

# Please use a compute node to build packages.
# salloc -Asglotzer9 --nodes=1 --ntasks-per-node=1 --cpus-per-task=36 --partition standard -t 8:00:00 --mem=144G

# Load modules used to build packages with native MPI and CUDA support.
module reset
module load gcc/10.3.0 openmpi/4.1.6 cuda/12.3.0

# Build package format 2
export CONDARC=.condarc

# Build on a node local SSD.
export CONDA_BLD_PATH=`mktemp --directory --tmpdir=/tmpssd conda-build-${USER}.XXXXXXXX`

function cleanup {
  rm -rf "$CONDA_BLD_PATH"
}

trap cleanup EXIT

conda build  "$@" \
      --skip-existing \
      --variants "{'cluster': ['greatlakes'], 'device': ['gpu']}" \
      --output-folder /nfs/turbo/glotzer/software/conda
