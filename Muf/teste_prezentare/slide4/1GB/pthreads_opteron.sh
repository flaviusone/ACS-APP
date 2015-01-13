#!/bin/bash
OMP_OUTPUT_H="../../../build/boyer_horspool_pthreads"
./$OMP_OUTPUT_H 1  ../../../inputs/test3 >> opteron/pthreads
./$OMP_OUTPUT_H 2  ../../../inputs/test3 >> opteron/pthreads
./$OMP_OUTPUT_H 4  ../../../inputs/test3 >> opteron/pthreads
./$OMP_OUTPUT_H 6  ../../../inputs/test3 >> opteron/pthreads
./$OMP_OUTPUT_H 8  ../../../inputs/test3 >> opteron/pthreads
./$OMP_OUTPUT_H 16 ../../../inputs/test3 >> opteron/pthreads
