#!/bin/bash

# Load modules used to build packages with native MPI support
module reset
module load gcc/10.3.0 openmpi/4.1.2

export OUTPUT_FOLDER=/ccs/proj/mat110/software/andes/conda

# Control ninja parallelism in hoomd builds
export SLURM_CPUS_PER_TASK=8

./build.sh "$@" \
    --skip-existing \
    --variants "{'cluster': ['andes'], 'device': ['cpu'], 'gpu_platform': ['none']}" \
    --output-folder $OUTPUT_FOLDER

chmod g-w $OUTPUT_FOLDER -R

