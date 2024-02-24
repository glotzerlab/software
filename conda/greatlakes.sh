#!/bin/bash

#SBATCH --job-name="glotzerlab-software build"
#SBATCH --account=sglotzer9
#SBATCH --partition=standard
#SBATCH --nodes=1
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=36
#SBATCH --mem=144g
#SBATCH --time=8:00:00

# Load modules used to build packages with native MPI and CUDA support.
module reset
module load gcc/10.3.0 openmpi/4.1.6 cuda/12.3.0

export TMPDIR=/tmpssd

./build.sh "$@" \
    --skip-existing \
    --variants "{'cluster': ['greatlakes'], 'device': ['gpu']}" \
    --output-folder /nfs/turbo/glotzer/software/conda
