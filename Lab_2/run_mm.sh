#!/bin/bash
module load compilers/gnu-4.6.3  
module load libraries/openmpi-1.6-gcc-4.6.3
mpirun -np $NSLOTS ./mpi_mm
