#!/bin/bash

#SBATCH --job-name="glotzerlab-software build"
#SBATCH --account=dmr140129
#SBATCH --partition=shared
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=32
#SBATCH --time=8:00:00

./conda-build-anvil.sh hoomd mpi4py

