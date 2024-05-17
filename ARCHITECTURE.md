# Glotzerlab software

## Conda packages

This repository hosts conda recipes to build HOOMD-blue and related software with MPI
and/or GPU support on HPC resources.

The `conda/` directory contains the files needed to construct these builds.
Subdirectories under `conda/` contain the recipes for each package. `conda/build.sh`
is the main script to build the package. The other `*.sh` scripts are drivers to
make the build on specific platforms. On systems that allow network connectivity from
compute nodes, these are SLURM scripts to be submitted with `sbatch`.
