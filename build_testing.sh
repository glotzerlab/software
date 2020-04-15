#!/bin/bash

set -u
set -e

python make_dockerfiles.py

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
OUTPUT=`mktemp -d -t singularity.XXXXXXX`

cp $DIR/test/*.py $DIR/docker/nompi/test
cp $DIR/check-requirements.py $DIR/docker/nompi
docker build $DIR/docker/nompi \
             -t software/nompi

cp $DIR/test/*.py $DIR/docker/greatlakes/test
cp $DIR/check-requirements.py $DIR/docker/greatlakes
docker build $DIR/docker/greatlakes \
             -t software/greatlakes

cp $DIR/test/*.py $DIR/docker/comet/test
cp $DIR/check-requirements.py $DIR/docker/comet
docker build $DIR/docker/comet \
             -t software/comet

cp $DIR/test/*.py $DIR/docker/bridges/test
cp $DIR/check-requirements.py $DIR/docker/bridges
docker build $DIR/docker/bridges \
             -t software/bridges

cp $DIR/test/*.py $DIR/docker/stampede2/test
cp $DIR/check-requirements.py $DIR/docker/stampede2
docker build $DIR/docker/stampede2 \
             -t software/stampede2

#for label in nompi greatlakes comet bridges stampede2
for label in nompi
do
    docker run -t --rm --privileged -v /var/run/docker.sock:/var/run/docker.sock -v ${OUTPUT}:/output singularityware/docker2singularity:v2.6 --name software-${label}-testing software/${label}
    mv ${OUTPUT}/*.simg /nfs/turbo/glotzer/containers/testing
done
rm -rf ${OUTPUT}
