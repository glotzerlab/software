#!/bin/bash
#SBATCH --job-name="test-cpu"
#SBATCH --partition=cpu
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

module load gcc/11.4.0 openmpi/4.1.6

set -x

singularity exec software.sif bash -c "set" | grep GLOTZERLAB

mpirun -n 1 singularity exec software.sif python3 serial-cpu.py

mpirun singularity exec software.sif python3 mpi-cpu.py

mpirun singularity exec software.sif /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

echo "Tests complete."
