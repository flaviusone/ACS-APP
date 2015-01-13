#!/bin/bash

rm nehalem/pthreads
rm opteron/pthreads
rm quad/pthreads

echo "Running all experiments slide 4"
qsub -cwd -q ibm-opteron.q 	pthreads_opteron.sh
qsub -cwd -q ibm-quad.q 	pthreads_quad.sh
qsub -cwd -q ibm-nehalem.q	pthreads_nehalem.sh
