#!/bin/bash
OMP_OUTPUT_H="../../../build/boyer_horspool_omp"
module load compilers/gnu-4.6.3
module load compilers/solarisstudio-12.3
./$OMP_OUTPUT_H 1  ../../../inputs/test3 >> opteron/omp
./$OMP_OUTPUT_H 2  ../../../inputs/test3 >> opteron/omp
./$OMP_OUTPUT_H 4  ../../../inputs/test3 >> opteron/omp
./$OMP_OUTPUT_H 6  ../../../inputs/test3 >> opteron/omp
#/opt/tools/compilers/solarisstudio12.3/lib/analyzer/lib/../../../bin/collect -o test.1.er -p on -S on -A on /export/home/acs/stud/f/flavius.tirnacop/flavius.tirnacop/APP/Muf/build/boyer_horspool_omp 4 ../../../inputs/test3
./$OMP_OUTPUT_H 16 ../../../inputs/test3 >> opteron/omp
