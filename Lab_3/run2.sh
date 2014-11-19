#!/bin/bash
qsub -q ibm-quad.q -cwd <<EOF
module load compilers/gnu-4.6.3
gcc -fopenmp HelloWorld.c -o Test
gcc -fopenmp pi.c -o pi
gcc -fopenmp pi2.c -o pi2
gcc -fopenmp pi3.c -o pi3
gcc -fopenmp pi4.c -o pi4
gcc -fopenmp pi5.c -o pi5
export OMP_NUM_THREADS=4
./pi5
EOF
