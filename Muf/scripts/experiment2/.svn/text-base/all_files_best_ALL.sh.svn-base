#!/bin/bash
OMP_OUTPUT_H="../../build/boyer_horspool_omp"

./$OMP_OUTPUT_H 8 ../../inputs/test1

./$OMP_OUTPUT_H 8 ../../inputs/test2

./$OMP_OUTPUT_H 8 ../../inputs/test3

./$OMP_OUTPUT_H 8 ../../inputs/test4


PTHREADS_OUTPUT_H="../../build/boyer_horspool_pthreads"

./$PTHREADS_OUTPUT_H 8 ../../inputs/test1

./$PTHREADS_OUTPUT_H 8 ../../inputs/test2

./$PTHREADS_OUTPUT_H 8 ../../inputs/test3

./$PTHREADS_OUTPUT_H 8 ../../inputs/test4


MPI_OUTPUT_H="../../build/boyer_horspool_mpi"
module load libraries/openmpi-1.6-gcc-4.6.3

mpirun -np 8 ./$MPI_OUTPUT_H ../../inputs/test1

mpirun -np 8 ./$MPI_OUTPUT_H ../../inputs/test2

mpirun -np 8 ./$MPI_OUTPUT_H ../../inputs/test3

mpirun -np 8 ./$MPI_OUTPUT_H ../../inputs/test4