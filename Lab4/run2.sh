#!/bin/bash
rm STDIN.*
qsub -q ibm-opteron.q -cwd <<EOF
module load compilers/gnu-4.6.3
gcc -fopenmp omp_mm.c -o omp_mm
export OMP_NUM_THREADS=4
./omp_mm
EOF

while [ ! -f STDIN.o* ]
do
  sleep 2
done
sleep 1
tail STDIN.o*
