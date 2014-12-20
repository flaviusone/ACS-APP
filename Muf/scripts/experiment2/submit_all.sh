#!/bin/bash
echo "Running experiment 2 - Fisiere diferite cu acc nr de threaduri si procese"
qsub -cwd -q ibm-opteron.q all_files_best_ALL.sh
qsub -cwd -q ibm-opteron.q all_files_best_MPI.sh
qsub -cwd -q ibm-opteron.q all_files_best_OMP.sh
qsub -cwd -q ibm-opteron.q all_files_best_PT.sh
