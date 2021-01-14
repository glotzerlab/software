#!/bin/bash
#SBATCH --job-name="test-cpu"
#SBATCH --partition=RM
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=128
#SBATCH -t 0:20:00

module load openmpi
rm -f test-results-cpu.out

mpirun -n 1 singularity exec software.simg python3 serial-cpu.py

mpirun singularity exec software.simg python3 mpi-cpu.py

mpirun singularity exec software.simg /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bw >> test-results-cpu.out
