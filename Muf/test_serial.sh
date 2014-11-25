#!/bin/bash
SERIAL_OUTPUT_H="build/boyer_horspool"
SERIAL_OUTPUT_BF="build/bruteforce"

echo "Building files..."
make build-serial-BF
make build-serial-H
echo "Running tests..."

#Run test 1 - Horspool
echo -e "\nRunning test 1 Horspool"
time ./$SERIAL_OUTPUT_H inputs/test1

#Run test 1 - Bruteforce
echo -e "\nRunning test 1 Bruteforce"
time ./$SERIAL_OUTPUT_H inputs/test1

#Run test 2 - Horspool
echo -e "\nRunning test 2 Horspool"
time ./$SERIAL_OUTPUT_H inputs/test2

#Run test 2 - Bruteforce
echo -e "\nRunning test 2 Bruteforce"
time ./$SERIAL_OUTPUT_H inputs/test2

#Run test 3 - Horspool
echo -e "\nRunning test 3 Horspool"
time ./$SERIAL_OUTPUT_H inputs/test3

#Run test 3 - Bruteforce
echo -e "\nRunning test 3 Bruteforce"
time ./$SERIAL_OUTPUT_H inputs/test3

echo "Done"
make clean