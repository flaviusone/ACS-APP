#!/bin/bash

rm nehalem/omp
rm opteron/omp
rm quad/omp

echo "Running all experiments slide 3"
qsub -cwd -q ibm-opteron.q 	omp_opteron.sh
qsub -cwd -q ibm-quad.q 	omp_quad.sh
qsub -cwd -q ibm-nehalem.q	omp_nehalem.sh
