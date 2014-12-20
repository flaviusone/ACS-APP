#!/bin/bash
echo "Running experiment 3 - Comparatie OMP/MPI/PT pe fisiere 1/10GB"
qsub -cwd -q ibm-opteron.q  GB10_ALL_var_threads.sh
qsub -cwd -q ibm-opteron.q  GB1_ALL_var_threads.sh
