CC=gcc
MPICC=mpicc
CFLAGS = -Wall

SERIAL_PATH_BM = serial/boyer_search.c
SERIAL_OUTPUT_BM = build/boyer_search

SERIAL_PATH_H = serial/boyer_horspool.c
SERIAL_OUTPUT_H = build/boyer_horspool

SERIAL_PATH_BF = serial/bruteforce.c
SERIAL_OUTPUT_BF = build/bruteforce

PARALLEL_PATH_H_OPENMP = paralel/boyer_horspool_openmp.c
PARALLEL_OUTPUT_H_OPENMP = build/horspool_openmp

PARALLEL_PATH_H_MPI = paralel/boyer_horspool_mpi.c
PARALLEL_OUTPUT_H_MPI = build/horspool_mpi

all: build-serial-BM build-serial-H build-serial-BF build-parallel-H-OpenMP build-mpi

build-serial-BM:
	$(CC) $(CFLAGS) $(SERIAL_PATH_BM) -o $(SERIAL_OUTPUT_BM)

build-serial-H:
	$(CC) $(CFLAGS) $(SERIAL_PATH_H) -o $(SERIAL_OUTPUT_H)

build-serial-BF:
	$(CC) $(CFLAGS) $(SERIAL_PATH_BF) -o $(SERIAL_OUTPUT_BF)

build-parallel-H-OpenMP:
	$(CC) $(CFLAGS) -fopenmp $(PARALLEL_PATH_H_OPENMP) -o $(PARALLEL_OUTPUT_H_OPENMP)

build-mpi:
	$(MPICC) $(CFLAGS) $(PARALLEL_PATH_H_MPI) -o $(PARALLEL_OUTPUT_H_MPI)

clean:
	rm build/*
