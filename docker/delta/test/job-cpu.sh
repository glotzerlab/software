#!/bin/bash
#SBATCH --job-name="test-cpu"
#SBATCH --partition=cpu
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

module load gcc/11.2.0 openmpi/4.1.2

rm -f test-results-cpu.out

mpirun -n 1 singularity exec software.sif python3 serial-cpu.py

mpirun singularity exec software.sif python3 mpi-cpu.py

mpirun singularity exec software.sif /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw >> test-results-cpu.out
