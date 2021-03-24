#!/bin/bash

set -u
set -e

usage()
    {
    echo "Usage: $0 -r repository [ -t tag ] [ system [ system [ ... ] ] ]"
    exit
    }

tag="$(date +%Y.%m.%d)"
repository=""

while getopts ":r:t:" o; do
    case "${o}" in
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
             ["bridges2"]="-t ${repository}/software:${tag}-rome-cuda10-mlx-openmpi3.6.2"
             ["stampede2"]="-t ${repository}/software:${tag}-skylakex-cuda10-hfi1-mvapich2.3"
)

for cluster in "$@"
do
    cp -a $DIR/test/*.py $DIR/docker/${cluster}/test
    cp -a $DIR/check-requirements.py $DIR/docker/${cluster}
    docker build $DIR/docker/${cluster} \
                -t ${repository}/software:${cluster} \
                -t ${repository}/software:${tag}-${cluster} \
                ${extra_tags[$cluster]}
done
