#!/bin/bash
#PBS -N test_cpu
#PBS -l nodes=2:ppn=20,walltime=00:10:00
#PBS -A sglotzer_fluxoe
#PBS -l gres=cpuslots
#PBS -l qos=flux
#PBS -q fluxoe
#PBS -j oe

# change to the job submission directory
cd ${PBS_O_WORKDIR}

module load gcc/5.4.0
module load openmpi/3.0.0/gcc/5.4.0

rm -f test-results-cpu.out

singularity exec software.simg python3 serial-cpu.py

mpirun -N 1 singularity exec software.simg python3 mpi-cpu.py

mpirun -N 1 singularity exec software.simg /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw >> test-results-cpu.out
