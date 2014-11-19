#!/bin/bash
SERIAL_OUTPUT="build/boyer_horspool"

echo "Building file..."
make build-serial
echo "Running..."

#Run test 1
./$SERIAL_OUTPUT inputs/test1


echo "Done"
make clean