#!/bin/bash
echo "Running experiment 1 - Acelasi fisier (1/10GB) variand nr de th si procese"
qsub -cwd -q ibm-nehalem.q 10GB_MPI_var_threads.sh
qsub -cwd -q ibm-nehalem.q 10GB_OMP_var_threads.sh
qsub -cwd -q ibm-nehalem.q 10GB_PT_var_threads.sh
qsub -cwd -q ibm-nehalem.q 1GB_MPI_var_threads.sh
qsub -cwd -q ibm-nehalem.q 1GB_OMP_var_threads.sh
qsub -cwd -q ibm-nehalem.q 1GB_PT_var_threads.sh