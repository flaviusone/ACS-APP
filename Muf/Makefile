CC=gcc
MPICC=mpicc
CFLAGS = -Wall

#######################################
# Varianta seriala cu Horspool
SERIAL_PATH_H = src/boyer_horspool.c
SERIAL_OUTPUT_H = build/boyer_horspool

# Varianta OMP cu Horspool
OMP_PATH_H = src/boyer_horspool_omp.c
OMP_OUTPUT_H = build/boyer_horspool_omp

# Varianta MPI cu Horspool
MPI_PATH_H = src/boyer_horspool_mpi.c
MPI_OUTPUT_H = build/boyer_horspool_mpi

# Varianta PTHREADS cu Horspool
PTHREADS_PATH_H = src/boyer_horspool_pthreads.c
PTHREADS_OUTPUT_H = build/boyer_horspool_pthreads
#######################################
# Varianta seriala cu Bruteforce
SERIAL_PATH_BF = src/bruteforce.c
SERIAL_OUTPUT_BF = build/bruteforce

# Varianta OMP cu Horspool
OMP_PATH_BF = src/bruteforce_omp.c
OMP_OUTPUT_BF = build/bruteforce_omp

# Varianta MPI cu Horspool
MPI_PATH_BF = src/bruteforce_mpi.c
MPI_OUTPUT_BF = build/bruteforce_mpi

# Varianta PTHREADS cu Horspool
PTHREADS_PATH_BF = src/bruteforce_pthreads.c
PTHREADS_OUTPUT_BF = build/bruteforce_pthreads
#######################################

###########################################################################
all: build-serial-H build-omp-H build-mpi-H build-pthreads-H build-serial-BF

build-serial-H:
	$(CC) $(CFLAGS) $(SERIAL_PATH_H) -o $(SERIAL_OUTPUT_H)

build-omp-H:
	$(CC) $(CFLAGS) -fopenmp -g $(OMP_PATH_H) -o $(OMP_OUTPUT_H)

build-mpi-H:
	$(MPICC) $(CFLAGS) $(MPI_PATH_H) -o $(MPI_OUTPUT_H)

build-pthreads-H:
	$(CC) $(CFLAGS) $(PTHREADS_PATH_H) -o $(PTHREADS_OUTPUT_H) -lpthread

###########################################################################
build-serial-BF:
	$(CC) $(CFLAGS) $(SERIAL_PATH_BF) -o $(SERIAL_OUTPUT_BF)

#build-omp-BF: #TODO - path e deja definit


#build-mpi-BF: #TODO - path e deja definit


#build-pthreads-BF: #TODO - path e deja definit

###########################################################################

clean:
	rm build/*
