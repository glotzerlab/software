#!/bin/bash

set -u
set -e

DATE_TAG=$(date +%Y.%m)
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

docker build $DIR/docker \
             -t glotzerlab/software:devel \

cp $DIR/test/*.py $DIR/docker/nompi
docker build $DIR/docker/nompi \
             -t glotzerlab/software:latest \
             -t glotzerlab/software:${DATE_TAG}-cuda9
echo "BootStrap: docker
From: glotzerlab/software:${DATE_TAG}-cuda9

" > $DIR/docker/Singularity.latest

cp $DIR/test/*.py $DIR/docker/flux
docker build $DIR/docker/flux \
             -t glotzerlab/software:flux \
             -t glotzerlab/software:${DATE_TAG}-cuda9-mlx-openmpi3.0.0
echo "BootStrap: docker
From: glotzerlab/software:${DATE_TAG}-cuda9-mlx-openmpi3.0.0

" > $DIR/docker/flux/Singularity.flux

cp $DIR/test/*.py $DIR/docker/comet
docker build $DIR/docker/comet \
             -t glotzerlab/software:comet \
             -t glotzerlab/software:${DATE_TAG}-haswell-cuda9-mlx-openmpi1.8.4
echo "BootStrap: docker
From: glotzerlab/software:${DATE_TAG}-haswell-cuda9-mlx-openmpi1.8.4

" > $DIR/docker/comet/Singularity.comet

cp $DIR/test/*.py $DIR/docker/bridges
docker build $DIR/docker/bridges \
             -t glotzerlab/software:bridges \
             -t glotzerlab/software:${DATE_TAG}-haswell-cuda9-hfi1-openmpi2.1.2
echo "BootStrap: docker
From: glotzerlab/software:${DATE_TAG}-haswell-cuda9-hfi1-openmpi2.1.2

" > $DIR/docker/bridges/Singularity.bridges

cp $DIR/test/*.py $DIR/docker/stampede2
docker build $DIR/docker/stampede2 \
             -t glotzerlab/software:stampede2 \
             -t glotzerlab/software:${DATE_TAG}-skylakex-cuda9-hfi1-mvapich2.3
echo "BootStrap: docker
From: glotzerlab/software:${DATE_TAG}-skylakex-cuda9-hfi1-mvapich2.3

" > $DIR/docker/stampede2/Singularity.stampede2
