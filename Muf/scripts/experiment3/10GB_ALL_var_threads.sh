#!/bin/bash
PTHREADS_OUTPUT_H="../../build/boyer_horspool_pthreads"
OMP_OUTPUT_H="../../build/boyer_horspool_omp"
MPI_OUTPUT_H="../../build/boyer_horspool_mpi"
module load libraries/openmpi-1.6-gcc-4.6.3

./$PTHREADS_OUTPUT_H 2 ../../inputs/test4

./$PTHREADS_OUTPUT_H 4 ../../inputs/test4

./$PTHREADS_OUTPUT_H 8 ../../inputs/test4

./$PTHREADS_OUTPUT_H 16 ../../inputs/test4


./$OMP_OUTPUT_H 2 ../../inputs/test4

./$OMP_OUTPUT_H 4 ../../inputs/test4

./$OMP_OUTPUT_H 8 ../../inputs/test4

./$OMP_OUTPUT_H 16 ../../inputs/test4


mpirun -np 2 ./$MPI_OUTPUT_H ../../inputs/test4

mpirun -np 4 ./$MPI_OUTPUT_H ../../inputs/test4

mpirun -np 8 ./$MPI_OUTPUT_H ../../inputs/test4

mpirun -np 16 ./$MPI_OUTPUT_H ../../inputs/test4