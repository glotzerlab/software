#!/bin/bash
#SBATCH --job-name="test-cpu"
#SBATCH --partition=RM
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=128
#SBATCH -t 0:20:00

module load openmpi/4.0.5-gcc10.2.0

set -x

singularity exec software.sif bash -c "set" | grep GLOTZERLAB

mpirun -n 1 singularity exec software.sif python3 serial-cpu.py

mpirun --npernode 1 singularity exec software.sif python3 mpi-cpu.py

mpirun --npernode 1 singularity exec software.sif /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bw

echo "Tests complete."
