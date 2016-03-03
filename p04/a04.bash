#!/bin/bash
#PBS -N a02-0
#PBS -q workq
#PBS -l select=1:ncpus=8:mpiprocs=8:mem=2gb:interconnect=mx
#PBS -l walltime=00:10:00
#PBS -j oe
#PBS -o $PBS_JOBID.log

cd $PBS_O_WORKDIR
module load gcc/4.8.1
module load openmpi/1.6.4
mpicxx gol.cpp

mpirun -n 2 ./a.out 20 20 1234 0 100 1000
