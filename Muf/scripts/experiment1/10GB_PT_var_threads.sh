#!/bin/bash
PTHREADS_OUTPUT_H="../../build/boyer_horspool_pthreads"

# #Run test 3 - Horspool
./$PTHREADS_OUTPUT_H 2 ../../inputs/test4

# #Run test 3 - Horspool
 ./$PTHREADS_OUTPUT_H 4 ../../inputs/test4

# #Run test 3 - Horspool
 ./$PTHREADS_OUTPUT_H 8 ../../inputs/test4

# #Run test 3 - Horspool
 ./$PTHREADS_OUTPUT_H 16 ../../inputs/test4
