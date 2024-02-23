#!/bin/bash

#SBATCH --job-name="glotzerlab-software build"
#SBATCH --account=sglotzer9
#SBATCH --partition=standard
#SBATCH --nodes=1
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=36
#SBATCH --mem=144g
#SBATCH --time=8:00:00

./conda-build-greatlakes.sh hoomd mpi4py

