#-----------------------------------------------------------------------
# Sun Application Tuning Seminar
#
# Script to LAB performance data using GNU plot
#
# Ruud van der Pas - Sun Microsystems
#-----------------------------------------------------------------------

set grid
set title 'MXV performance: version parallelized with OpenMP'
set xlabel 'Memory Footprint (KByte)'
set ylabel 'Performance (Mflop/s)'
set xrange [.25:524288]
set xtics .25,4,262144
set logscale x 2
set yrange [1:*]

plot 'omp_1_procs.dat' using 3:4\
     title 'Row OpenMP - 1 proc' with linespoints 1, \
     'omp_2_procs.dat' using 3:4\
     title 'Row OpenMP - 2 procs' with linespoints 2

pause -1 'Press <Return> to plot data for the column version'

plot 'omp_1_procs.dat' using 3:5\
     title 'Column OpenMP - 1 proc' with linespoints 1, \
     'omp_2_procs.dat' using 3:5\
     title 'Column OpenMP - 2 procs' with linespoints 2

pause -1 'Press <Return> to compare data - row version'

plot 'serial.dat' using 3:4\
     title 'Row - serial version' with linespoints 1, \
     'par_1_procs.dat' using 3:4\
     title 'Row autopar - 1 proc' with linespoints 2, \
     'omp_1_procs.dat' using 3:4\
     title 'Row OpenMP - 1 proc' with linespoints 3

pause -1 'Press <Return> to compare data - column version'

plot 'serial.dat' using 3:5\
     title 'Column - serial version' with linespoints 1, \
     'par_1_procs.dat' using 3:5\
     title 'Column autopar - 1 proc' with linespoints 2, \
     'omp_1_procs.dat' using 3:5\
     title 'Column OpenMP - 1 proc' with linespoints 3

pause -1 'Press <Return> to compare data - single processor'

plot 'omp_1_procs.dat' using 3:4\
     title 'Row OpenMP - 1 proc' with linespoints 1, \
     'par_1_procs.dat' using 3:4\
     title 'Row autopar - 1 proc' with linespoints 2, \
     'omp_1_procs.dat' using 3:5\
     title 'Column OpenMP - 1 proc' with linespoints 3, \
     'par_1_procs.dat' using 3:5\
     title 'Column autopar - 1 proc' with linespoints 4, \
     'omp_1_procs.dat' using 3:6\
     title 'Parallel library version - 1 proc' with linespoints 5

pause -1 'Press <Return> to compare data - two processors'

plot 'omp_2_procs.dat' using 3:4\
     title 'Row OpenMP - 2 procs' with linespoints 1, \
     'par_2_procs.dat' using 3:4\
     title 'Row autopar - 2 procs' with linespoints 2, \
     'omp_2_procs.dat' using 3:5\
     title 'Column OpenMP - 2 procs' with linespoints 3, \
     'par_2_procs.dat' using 3:5\
     title 'Column autopar - 2 procs' with linespoints 4, \
     'omp_2_procs.dat' using 3:6\
     title 'Parallel library version - 2 procs' with linespoints 5

pause -1 'Press <Return> to stop'
