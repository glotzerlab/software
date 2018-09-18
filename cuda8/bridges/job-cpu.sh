#!/bin/bash
#SBATCH --job-name="test-cpu"
#SBATCH --partition=RM-small
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=28
#SBATCH --export=ALL
#SBATCH -t 0:10:00

source /etc/profile.d/modules.sh
module load singularity
module unload intel
module load mpi/gcc_openmpi

rm -f test-results-cpu.out

mpirun -n 1 singularity exec software.simg python3 serial-cpu.py

mpirun singularity exec software.simg python3 mpi-cpu.py

mpirun singularity exec software.simg /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw >> test-results-cpu.out
