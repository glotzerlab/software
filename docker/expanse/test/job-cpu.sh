#!/bin/bash
#SBATCH --job-name="test-cpu"
#SBATCH --partition=compute
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH -t 0:10:00

module load cpu/0.15.4 singularitypro gcc/9.2.0 openmpi/4.1.1

set -x

singularity exec software.sif bash -c "set" | grep GLOTZERLAB

singularity exec software.sif python3 serial-cpu.py

mpirun --npernode 1 singularity exec software.sif python3 mpi-cpu.py

mpirun --npernode 1 singularity exec software.sif /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

echo "Tests complete."
