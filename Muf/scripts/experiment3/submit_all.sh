#!/bin/bash
echo "Running experiment 3 - Comparatie OMP/MPI/PT pe fisiere 1/10GB"
qsub -cwd -q ibm-nehalem.q  10GB_ALL_var_threads.sh
qsub -cwd -q ibm-nehalem.q  1GB_ALL_var_threads.sh
