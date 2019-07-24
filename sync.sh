#!/bin/bash

set -u
set -e

umask 022

# docker push glotzerlab/software

rsync -rvt --delete-after /nfs/turbo/glotzer/containers/glotzerlab login.itd.umich.edu:/afs/umich.edu/group/g/glotzweb/Downloads
