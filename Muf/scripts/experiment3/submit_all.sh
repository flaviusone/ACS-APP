#!/bin/bash
echo "Running experiment 3 - Comparatie OMP/MPI/PT pe fisiere 1/10GB"
qsub -cwd -q ibm-nehalem.q  GB10_ALL_var_threads.sh
qsub -cwd -q ibm-nehalem.q  GB1_ALL_var_threads.sh
