#!/bin/bash

#SBATCH --job-name="glotzerlab-software build"
#SBATCH --account=bbgw-delta-gpu
#SBATCH --partition=gpuA40x4
#SBATCH --nodes=1
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=16
#SBATCH --mem=48g
#SBATCH --gpus=1
#SBATCH --time=8:00:00

# TODO: rewrite to use CPU account when it is renewed
./conda-build-delta.sh hoomd mpi4py
