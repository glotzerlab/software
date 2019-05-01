#!/bin/bash

set -u
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
OUTPUT=`mktemp -d -t singularity.XXXXXXX`

mkdir -p /tmp/

cp $DIR/test/*.py $DIR/docker/nompi
docker build $DIR/docker/nompi \
             -t software/vislab
docker run -t --rm --privileged -v /var/run/docker.sock:/var/run/docker.sock -v ${OUTPUT}:/output singularityware/docker2singularity:v2.6 --name software-vislab-testing software/vislab
mv ${OUTPUT}/*.simg /nfs/turbo/glotzer/containers/testing

cp $DIR/test/*.py $DIR/docker/comet
docker build $DIR/docker/comet \
             -t software/comet
docker run -t --rm --privileged -v /var/run/docker.sock:/var/run/docker.sock -v ${OUTPUT}:/output singularityware/docker2singularity:v2.6 --name software-comet-testing software/comet
mv ${OUTPUT}/*.simg /nfs/turbo/glotzer/containers/testing

cp $DIR/test/*.py $DIR/docker/flux
docker build $DIR/docker/flux \
             -t software/flux
docker run -t --rm --privileged -v /var/run/docker.sock:/var/run/docker.sock -v ${OUTPUT}:/output singularityware/docker2singularity:v2.6 --name software-flux-testing software/flux
mv ${OUTPUT}/*.simg /nfs/turbo/glotzer/containers/testing

cp $DIR/test/*.py $DIR/docker/bridges
docker build $DIR/docker/bridges \
             -t software/bridges
docker run -t --rm --privileged -v /var/run/docker.sock:/var/run/docker.sock -v ${OUTPUT}:/output singularityware/docker2singularity:v2.6 --name software-bridges-testing software/bridges
mv ${OUTPUT}/*.simg /nfs/turbo/glotzer/containers/testing

cp $DIR/test/*.py $DIR/docker/stampede2
docker build $DIR/docker/stampede2 \
             -t software/stampede2
docker run -t --rm --privileged -v /var/run/docker.sock:/var/run/docker.sock -v ${OUTPUT}:/output singularityware/docker2singularity:v2.6 --name software-stampede2-testing software/stampede2
mv ${OUTPUT}/*.simg /nfs/turbo/glotzer/containers/testing

rm -rf ${OUTPUT}
