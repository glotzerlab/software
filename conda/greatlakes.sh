#!/bin/bash

#SBATCH --job-name="glotzerlab-software build"
#SBATCH --account=sglotzer9
#SBATCH --partition=standard
#SBATCH --nodes=1
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=8
#SBATCH --mem=144g
#SBATCH --time=8:00:00

export OUTPUT_FOLDER=/nfs/turbo/glotzer/software/conda
unset CMAKE_PREFIX_PATH

# Load modules used to build packages with native MPI and CUDA support.
module reset
module load gcc/10.3.0 openmpi/4.1.6 cuda/12.3.0

echo -n "Executing on host: " && hostname

if [ -d "/tmpssd" ]; then
  export TMPDIR=/tmpssd
  echo "Using /tmpsdd for build."
else
  export TMPDIR=/tmp
  echo "Warning! /tmpssd does not exist. Using /tmp for build."
fi

./build.sh "$@" \
    --skip-existing \
    --variants "{'cluster': ['greatlakes'], 'device': ['gpu'], 'gpu_platform': ['CUDA']}" \
    --output-folder $OUTPUT_FOLDER

chmod g-w $OUTPUT_FOLDER -R
