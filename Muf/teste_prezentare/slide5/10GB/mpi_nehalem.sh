#!/bin/bash
module load libraries/openmpi-1.6-gcc-4.6.3
MPI_OUTPUT_H="../../../build/boyer_horspool_mpi"
mpirun -np 1  ./$MPI_OUTPUT_H ../../../inputs/test4 >> nehalem/mpi
mpirun -np 2  ./$MPI_OUTPUT_H ../../../inputs/test4 >> nehalem/mpi
mpirun -np 4  ./$MPI_OUTPUT_H ../../../inputs/test4 >> nehalem/mpi
mpirun -np 6  ./$MPI_OUTPUT_H ../../../inputs/test4 >> nehalem/mpi
mpirun -np 8  ./$MPI_OUTPUT_H ../../../inputs/test4 >> nehalem/mpi
mpirun -np 16 ./$MPI_OUTPUT_H ../../../inputs/test4 >> nehalem/mpi
