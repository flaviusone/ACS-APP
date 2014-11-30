#!/bin/bash
SERIAL_OUTPUT_BM="build/boyer_search"
SERIAL_OUTPUT_H="build/boyer_horspool"
SERIAL_OUTPUT_BF="build/bruteforce"
PARALLEL_OUTPUT_H="build/horspool_openmp"

echo "Building files..."
make build-serial-BM
make build-serial-BF
make build-serial-H
make build-parallel-H-OpenMP
echo "Running tests..."

#Run test 1 - Horspool
echo -e "\nRunning test 1 Horspool"
./$SERIAL_OUTPUT_H inputs/test1

#Run test 1 - Bruteforce
echo -e "\nRunning test 1 Bruteforce"
./$SERIAL_OUTPUT_BF inputs/test1

#Run test 2 - Horspool
echo -e "\nRunning test 2 Horspool"
./$SERIAL_OUTPUT_H inputs/test2

#Run test 2 - Bruteforce
echo -e "\nRunning test 2 Bruteforce"
./$SERIAL_OUTPUT_BF inputs/test2

#Run test 3 - Horspool
echo -e "\nRunning test 3 Horspool"
./$SERIAL_OUTPUT_H inputs/test3

#Run test 3 - Bruteforce
echo -e "\nRunning test 3 Bruteforce"
./$SERIAL_OUTPUT_BF inputs/test3

#Run test 1 - Horspool
echo -e "\nRunning test 1 Horspool OpenMP"
./$PARALLEL_OUTPUT_H inputs/test1

#Run test 2 - Horspool
echo -e "\nRunning test 2 Horspool OpenMP"
./$PARALLEL_OUTPUT_H inputs/test2

#Run test 3 - Horspool
echo -e "\nRunning test 3 Horspool OpenMP"
./$PARALLEL_OUTPUT_H inputs/test3

echo "Done"
make clean




# #Run test 1 - BM
# echo -e "\nRunning test 1 BM"
# time ./$SERIAL_OUTPUT_BM inputs/test1

# #Run test 1 - BM
# echo -e "\nRunning test 1 BM"
# time ./$SERIAL_OUTPUT_BM inputs/test2

# #Run test 1 - BM
# echo -e "\nRunning test 1 BM"
# time ./$SERIAL_OUTPUT_BM inputs/test3