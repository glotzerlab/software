#!/bin/bash

set -u
set -e

usage()
    {
    echo "Usage: $0 -r repository [ -t tag ] [ -s ] [ -k ] [ system [ system [ ... ] ] ]"
    exit
    }

tag="$(date +%Y.%m.%d)"
build_singularity=false
skip_docker=false
repository=""

while getopts ":skr:t:" o; do
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
        k)
            skip_docker=true
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
             ["bridges2"]="-t ${repository}/software:${tag}-rome-cuda10-mlx-openmpi3.6.2"
             ["stampede2"]="-t ${repository}/software:${tag}-skylakex-cuda10-hfi1-mvapich2.3"
)

if [ "$skip_docker" = false ] ; then
    for cluster in "$@"
    do
        cp -a $DIR/test/*.py $DIR/docker/${cluster}/test
        cp -a $DIR/check-requirements.py $DIR/docker/${cluster}
        docker build $DIR/docker/${cluster} \
                    -t ${repository}/software:${cluster} \
                    -t ${repository}/software:${tag}-${cluster} \
                    ${extra_tags[$cluster]}
    done
fi

if [ "$build_singularity" = true ] ; then
    for label in "$@"
    do
        docker run -t --rm --privileged -v /var/run/docker.sock:/var/run/docker.sock \
                   -v ${OUTPUT}:/output singularityware/docker2singularity:v2.6 \
                   --name software-${label} ${repository}/software:${tag}-${label}
        mkdir -p /nfs/turbo/glotzer/containers/${repository}
        mv ${OUTPUT}/*.simg /nfs/turbo/glotzer/containers/${repository}
    done
fi
