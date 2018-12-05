#!/bin/bash
#SBATCH --job-name="test-cpu"
#SBATCH --partition=debug
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=24
#SBATCH --export=ALL
#SBATCH -t 0:10:00

module load singularity
module unload mvapich2_ib
module load openmpi_ib

rm -f test-results-cpu.out

ibrun -n 1 singularity exec software.simg python3 serial-cpu.py

ibrun --npernode 1 singularity exec software.simg python3 mpi-cpu.py

ibrun --npernode 1 singularity exec software.simg /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw >> test-results-cpu.out
