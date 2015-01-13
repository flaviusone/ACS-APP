#!/bin/bash
SERIAL_OUTPUT_H="../../../build/boyer_horspool"
./$SERIAL_OUTPUT_H ../../../inputs/test1 >> opteron/serial
./$SERIAL_OUTPUT_H ../../../inputs/test2 >> opteron/serial
./$SERIAL_OUTPUT_H ../../../inputs/test3 >> opteron/serial
./$SERIAL_OUTPUT_H ../../../inputs/test4 >> opteron/serial
