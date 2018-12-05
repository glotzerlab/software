#!/bin/bash
#SBATCH --job-name="test-cpu"
#SBATCH --partition=skx-normal
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --export=ALL
#SBATCH -t 0:10:00

module load tacc-singularity
module load mvapich2

rm -f test-results-cpu.out

singularity exec software.simg python3 serial-cpu.py

ibrun -n 2 singularity exec software.simg python3 mpi-cpu.py

ibrun -n 2 singularity exec software.simg /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw >> test-results-cpu.out
