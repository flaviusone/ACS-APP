#!/bin/bash
MPI_OUTPUT_H="../../build/boyer_horspool_mpi"
module load libraries/openmpi-1.6-gcc-4.6.3

mpirun -np 2 ./$MPI_OUTPUT_H ../../inputs/test3

mpirun -np 4 ./$MPI_OUTPUT_H ../../inputs/test3

mpirun -np 8 ./$MPI_OUTPUT_H ../../inputs/test3

mpirun -np 16 ./$MPI_OUTPUT_H ../../inputs/test3