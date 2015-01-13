#!/bin/bash

rm nehalem/serial
rm opteron/serial
rm quad/serial

echo "Running all experiments slide 2"
qsub -cwd -q ibm-opteron.q 	BHserial_opteron.sh
qsub -cwd -q ibm-quad.q 	BHserial_quad.sh
qsub -cwd -q ibm-nehalem.q	BHserial_nehalem.sh
