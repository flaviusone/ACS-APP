#!/bin/bash

rm nehalem/mpi
rm opteron/mpi
rm quad/mpi

echo "Running all experiments slide 5"
#qsub -cwd -q ibm-opteron.q 	mpi_opteron.sh
#qsub -cwd -q ibm-quad.q 	mpi_quad.sh
qsub -cwd -q ibm-nehalem.q	mpi_nehalem.sh
