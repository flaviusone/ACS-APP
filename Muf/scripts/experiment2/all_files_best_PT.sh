#!/bin/bash
PTHREADS_OUTPUT_H="../../build/boyer_horspool_pthreads"

./$PTHREADS_OUTPUT_H 8 ../../inputs/test1

./$PTHREADS_OUTPUT_H 8 ../../inputs/test2

./$PTHREADS_OUTPUT_H 8 ../../inputs/test3

./$PTHREADS_OUTPUT_H 8 ../../inputs/test4
