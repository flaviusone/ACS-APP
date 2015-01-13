#!/bin/bash
SERIAL_OUTPUT_H="../../../build/boyer_horspool"
./$SERIAL_OUTPUT_H ../../../inputs/test1 >> quad/serial
./$SERIAL_OUTPUT_H ../../../inputs/test2 >> quad/serial
./$SERIAL_OUTPUT_H ../../../inputs/test3 >> quad/serial
./$SERIAL_OUTPUT_H ../../../inputs/test4 >> quad/serial
