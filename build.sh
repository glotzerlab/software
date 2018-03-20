#!/bin/bash

DATE_TAG=$(date +%Y.%m)
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

docker build $DIR/cuda8 \
             -t glotzerlab/software:latest \
             -t glotzerlab/software:cuda8 \
             -t glotzerlab/software:${DATE_TAG}-cuda8

docker build $DIR/cuda8/openmpi3.0 \
             -t glotzerlab/software:openmpi3.0 \
             -t glotzerlab/software:cuda8-openmpi3.0 \
             -t glotzerlab/software:${DATE_TAG}-cuda8-openmpi3.0
