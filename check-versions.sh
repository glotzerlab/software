#!/bin/bash

packages="fresnel freud garnett gsd hoomd-blue libgetar pythia rowan plato signac signac-flow"

output="package git-version pkgver\n"
for package in ${packages}
do
    repos=https://github.com/glotzerlab/${package}

    git_version=$(git ls-remote --tags ${repos} | sort -t '/' -k 3 -k 4 -V | grep -v { | awk -F/ '{ print $3 }' | tail -n1)
    if [ -z "${git_version}" ]
    then
        git_version="n/a"
    fi

    pkgver=$( python -c "import make_dockerfiles; print(make_dockerfiles.repo_version['$package']);" )
    prefix=""

    output+="${package} ${git_version} ${pkgver}\n"
done

echo -e ${output} | column -t
