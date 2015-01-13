#!/bin/bash
SERIAL_OUTPUT_H="../../../build/boyer_horspool"
./$SERIAL_OUTPUT_H ../../../inputs/test1 >> nehalem/serial
./$SERIAL_OUTPUT_H ../../../inputs/test2 >> nehalem/serial
./$SERIAL_OUTPUT_H ../../../inputs/test3 >> nehalem/serial
./$SERIAL_OUTPUT_H ../../../inputs/test4 >> nehalem/serial
