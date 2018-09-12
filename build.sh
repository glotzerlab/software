#!/bin/bash

set -u
set -e

DATE_TAG=$(date +%Y.%m)
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

docker build $DIR/cuda8 \
             -t glotzerlab/software:latest \
             -t glotzerlab/software:cuda8 \
             -t glotzerlab/software:${DATE_TAG}-cuda8
echo "BootStrap: docker\nFrom: glotzerlab/software:${DATE_TAG}-cuda8" > $DIR/cuda8/Singularity.latest

docker build $DIR/cuda8/flux \
             -t glotzerlab/software:flux \
             -t glotzerlab/software:cuda8-flux \
             -t glotzerlab/software:${DATE_TAG}-cuda8-mlx-openmpi3.0.0 \
             -t glotzerlab/software:${DATE_TAG}-cuda8-flux
echo "BootStrap: docker\nFrom: glotzerlab/software:${DATE_TAG}-cuda8-flux" > $DIR/cuda8/flux/Singularity.flux

docker build $DIR/cuda8/comet \
             -t glotzerlab/software:comet \
             -t glotzerlab/software:cuda8-comet \
             -t glotzerlab/software:${DATE_TAG}-cuda8-mlx-openmpi1.8.4 \
             -t glotzerlab/software:${DATE_TAG}-cuda8-comet
echo "BootStrap: docker\nFrom: glotzerlab/software:${DATE_TAG}-cuda8-comet" > $DIR/cuda8/comet/Singularity.comet

docker build $DIR/cuda8/bridges \
             -t glotzerlab/software:bridges \
             -t glotzerlab/software:cuda8-bridges \
             -t glotzerlab/software:${DATE_TAG}-cuda8-hfi1-openmpi1.10.4 \
             -t glotzerlab/software:${DATE_TAG}-cuda8-bridges
echo "BootStrap: docker\nFrom: glotzerlab/software:${DATE_TAG}-cuda8-bridges" > $DIR/cuda8/bridges/Singularity.bridges

docker build $DIR/cuda8/stampede2 \
             -t glotzerlab/software:stampede2 \
             -t glotzerlab/software:cuda8-stampede2 \
             -t glotzerlab/software:${DATE_TAG}-cuda8-hfi1-mvapich2.3 \
             -t glotzerlab/software:${DATE_TAG}-cuda8-stampede2
echo "BootStrap: docker\nFrom: glotzerlab/software:${DATE_TAG}-cuda8-stampede2" > $DIR/cuda8/stampede2/Singularity.stampede2
