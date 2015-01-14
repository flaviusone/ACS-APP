#!/bin/bash
module load libraries/openmpi-1.6-gcc-4.6.3
module load compilers/gnu-4.6.3
module load compilers/solarisstudio-12.3
MPI_OUTPUT_H="../../../build/boyer_horspool_mpi"
mpirun -np 1  ./$MPI_OUTPUT_H ../../../inputs/test3 >> nehalem/mpi
mpirun -np 2  ./$MPI_OUTPUT_H ../../../inputs/test3 >> nehalem/mpi
mpirun -np 4  ./$MPI_OUTPUT_H ../../../inputs/test3 >> nehalem/mpi
mpirun -np 6  ./$MPI_OUTPUT_H ../../../inputs/test3 >> nehalem/mpi
mpirun -np 8  ./$MPI_OUTPUT_H ../../../inputs/test3 >> nehalem/mpi
#mpirun -np 4 /opt/tools/compilers/solarisstudio12.3/lib/analyzer/lib/../../../bin/collect -o test.1.er -p on -S on -A on /export/home/acs/stud/f/flavius.tirnacop/flavius.tirnacop/APP/Muf/build/boyer_horspool_mpi ../../../inputs/test3

mpirun -np 16 ./$MPI_OUTPUT_H ../../../inputs/test3 >> nehalem/mpi
