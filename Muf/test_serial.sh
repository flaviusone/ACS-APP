#!/bin/bash
SERIAL_OUTPUT="build/boyer_horspool"

echo "Building file..."
make build-serial
echo "Running..."

#Run test 1
# time ./$SERIAL_OUTPUT inputs/test1
#Run test 2
time ./$SERIAL_OUTPUT inputs/test2
#Run test 3
# time ./$SERIAL_OUTPUT inputs/test3


echo "Done"
make clean