#!/bin/bash
echo "Running experiment 1 - Acelasi fisier (1/10GB) variand nr de th si procese"
qsub -cwd -q ibm-nehalem.q GB10_MPI_var_threads.sh
qsub -cwd -q ibm-nehalem.q GB10_OMP_var_threads.sh
qsub -cwd -q ibm-nehalem.q GB10_PT_var_threads.sh
qsub -cwd -q ibm-nehalem.q GB1_MPI_var_threads.sh
qsub -cwd -q ibm-nehalem.q GB1_OMP_var_threads.sh
qsub -cwd -q ibm-nehalem.q GB1_PT_var_threads.sh