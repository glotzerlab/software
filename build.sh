#!/bin/bash

set -u
set -e

usage()
    {
    echo "Usage: $0 -r repository [ -s ] [ -t tag ] [ system [ system [ ... ] ] ]"
    exit
    }

tag="$(date +%Y.%m)"
build_singularity=false
repository=""

while getopts ":sr:t:" o; do
    case "${o}" in
        s)
            build_singularity=true
            ;;
        r)
            repository=${OPTARG}
            ;;
        t)
            tag=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ -z "${repository}" ]; then
    usage
fi

python3 make_dockerfiles.py

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
OUTPUT=`mktemp -d -t singularity.XXXXXXX`

umask 022

declare -A extra_tags
extra_tags=( ["nompi"]="-t ${repository}/software:latest -t ${repository}/software:${tag}-cuda10"
             ["greatlakes"]="-t ${repository}/software:${tag}-skylakex-cuda10-mlx-openmpi4.0.1"
             ["comet"]="-t ${repository}/software:${tag}-haswell-cuda9-mlx-openmpi1.8.4"
             ["bridges"]="-t ${repository}/software:${tag}-haswell-cuda10-hfi1-openmpi2.1.2"
             ["stampede2"]="-t ${repository}/software:${tag}-skylakex-cuda10-hfi1-mvapich2.3"
)

for cluster in "$@"
do
    cp $DIR/test/*.py $DIR/docker/${cluster}/test
    cp $DIR/check-requirements.py $DIR/docker/${cluster}
    docker build $DIR/docker/${cluster} \
                -t ${repository}/software:${cluster} \
                ${extra_tags[$cluster]}
done

if [ "$build_singularity" = true ] ; then
    for label in "$@"
    do
        docker run -t --rm --privileged -v /var/run/docker.sock:/var/run/docker.sock \
                   -v ${OUTPUT}:/output singularityware/docker2singularity:v2.6 \
                   --name software-${label} ${repository}/software:${label}
        mkdir -p /nfs/turbo/glotzer/containers/${repository}
        mv ${OUTPUT}/*.simg /nfs/turbo/glotzer/containers/${repository}
    done
fi
