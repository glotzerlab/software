#!/bin/bash

set -u
set -e

umask 022

# docker push glotzerlab/software

rsync -rvt --progress --delete-after /nfs/turbo/glotzer/containers/glotzerlab greatlakes.arc-ts.umich.edu:/afs/umich.edu/group/g/glotzweb/Downloads
