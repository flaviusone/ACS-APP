#!/bin/bash
SERIAL_OUTPUT="build/boyer_horspool"

echo "Building file..."
make build-serial
echo "Running..."
./$SERIAL_OUTPUT
echo "Done"
make clean