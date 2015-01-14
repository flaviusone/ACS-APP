#!/bin/bash
module load compilers/gnu-4.6.3
module load compilers/solarisstudio-12.3

OMP_OUTPUT_H="../../../build/boyer_horspool_pthreads"
#/opt/tools/compilers/solarisstudio12.3/lib/analyzer/lib/../../../bin/collect -o test.1.er -p on -S on -A on /export/home/acs/stud/f/flavius.tirnacop/flavius.tirnacop/APP/Muf/build/boyer_horspool_pthreads 4 ../../../inputs/test3
#/opt/tools/compilers/solarisstudio12.3/lib/analyzer/lib/../../../bin/collect -o test.2.er -p on -S on -A on /export/home/acs/stud/f/flavius.tirnacop/flavius.tirnacop/APP/Muf/build/boyer_horspool_pthreads 8 ../../../inputs/test3

./$OMP_OUTPUT_H 1  ../../../inputs/test3 >> opteron/pthreads
./$OMP_OUTPUT_H 2  ../../../inputs/test3 >> opteron/pthreads
./$OMP_OUTPUT_H 4  ../../../inputs/test3 >> opteron/pthreads
./$OMP_OUTPUT_H 6  ../../../inputs/test3 >> opteron/pthreads
./$OMP_OUTPUT_H 8  ../../../inputs/test3 >> opteron/pthreads
./$OMP_OUTPUT_H 16 ../../../inputs/test3 >> opteron/pthreads
