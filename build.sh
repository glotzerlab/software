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

declare -A extra_tags
extra_tags=( ["nompi"]="-t ${repository}/software:latest"
             ["greatlakes"]=""
             ["expanse"]=""
             ["bridges2"]=""
             ["stampede2"]=""
)

for cluster in "$@"
do
    cp -a $DIR/test/*.py $DIR/docker/${cluster}/test
    cp -a requirements*.txt $DIR/docker/${cluster}
    docker build $DIR/docker/${cluster} \
                -t ${repository}/software:${cluster} \
                -t ${repository}/software:${tag}-${cluster} \
                ${extra_tags[$cluster]} \
                --build-arg GIT_SHA=$(git rev-parse HEAD) \
                --build-arg GIT_BRANCH=$(git branch --show-current) \
                --build-arg CONFIGURATION=${cluster} \
                --build-arg TAG=${tag}
done
