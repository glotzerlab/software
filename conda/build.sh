#!/bin/bash

# Build package format 2
export CONDARC=.condarc

# Build on a node local SSD.
export CONDA_BLD_PATH=`mktemp --directory conda-build-${USER}.XXXXXXXX --tmpdir`

function cleanup {
  rm -rf "$CONDA_BLD_PATH"
}

trap cleanup EXIT

conda mambabuild  "$@"
