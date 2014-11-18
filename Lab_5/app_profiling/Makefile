build:
	cc -xO3 -g -o app_lab4 openmp_stack_quicksort.c


build_omp:
	cc -xO3 -xopenmp -g -xloopinfo -L/opt/sun/sunstudio12.1/rtlibs/amd64 -o app_lab4_omp openmp_stack_quicksort.c

clean:
	rm -Rf app_lab4_omp app_lab4
