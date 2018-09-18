#!/bin/bash

set -u
set -e

DATE_TAG=$(date +%Y.%m)
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

docker build $DIR/cuda8 \
             -t glotzerlab/software:devel \

cp $DIR/test/*.py $DIR/cuda8/nompi
docker build $DIR/cuda8/nompi \
             -t glotzerlab/software:latest \
             -t glotzerlab/software:${DATE_TAG}-cuda8
echo "BootStrap: docker
From: glotzerlab/software:${DATE_TAG}-cuda8" > $DIR/cuda8/Singularity.latest

cp $DIR/test/*.py $DIR/cuda8/flux
docker build $DIR/cuda8/flux \
             -t glotzerlab/software:flux \
             -t glotzerlab/software:${DATE_TAG}-cuda8-mlx-openmpi3.0.0
echo "BootStrap: docker
From: glotzerlab/software:${DATE_TAG}-cuda8-mlx-openmpi3.0.0" > $DIR/cuda8/flux/Singularity.flux

cp $DIR/test/*.py $DIR/cuda8/comet
docker build $DIR/cuda8/comet \
             -t glotzerlab/software:comet \
             -t glotzerlab/software:${DATE_TAG}-haswell-cuda8-mlx-openmpi1.8.4
echo "BootStrap: docker
From: glotzerlab/software:${DATE_TAG}-haswell-cuda8-mlx-openmpi1.8.4" > $DIR/cuda8/comet/Singularity.comet

cp $DIR/test/*.py $DIR/cuda8/bridges
docker build $DIR/cuda8/bridges \
             -t glotzerlab/software:bridges \
             -t glotzerlab/software:${DATE_TAG}-haswell-cuda8-hfi1-openmpi2.1.2
echo "BootStrap: docker
From: glotzerlab/software:${DATE_TAG}-haswell-cuda8-hfi1-openmpi2.1.2" > $DIR/cuda8/bridges/Singularity.bridges

cp $DIR/test/*.py $DIR/cuda8/stampede2
docker build $DIR/cuda8/stampede2 \
             -t glotzerlab/software:stampede2 \
             -t glotzerlab/software:${DATE_TAG}-skylakex-cuda8-hfi1-mvapich2.3
echo "BootStrap: docker
From: glotzerlab/software:${DATE_TAG}-skylakex-cuda8-hfi1-mvapich2.3" > $DIR/cuda8/stampede2/Singularity.stampede2
