#-----------------------------------------------------------------------
# Sun Application Tuning Seminar
#
# Script to LAB performance data using GNU plot
#
# Ruud van der Pas - Sun Microsystems
#-----------------------------------------------------------------------

set grid
set title 'MXV performance: version parallelized with OpenMP (using thresholds)'
set xlabel 'Memory Footprint (KByte)'
set ylabel 'Performance (Mflop/s)'
set xrange [.25:524288]
set xtics .25,4,262144
set logscale x 2
set yrange [1:*]

plot 'ompth_1_procs.dat' using 3:4\
     title 'Row OpenMP (threshold) - 1 proc' with linespoints 1, \
     'ompth_2_procs.dat' using 3:4\
     title 'Row OpenMP (threshold) - 2 procs' with linespoints 2

pause -1 'Press <Return> to plot data for the column version'

plot 'ompth_1_procs.dat' using 3:5\
     title 'Column OpenMP (threshold) - 1 proc' with linespoints 1, \
     'ompth_2_procs.dat' using 3:5\
     title 'Column OpenMP (threshold) - 2 procs' with linespoints 2

pause -1 'Press <Return> to compare data - row version - single proc'

plot 'serial.dat' using 3:4\
     title 'Row - serial version' with linespoints 1, \
     'omp_1_procs.dat' using 3:4\
     title 'Row OpenMP - 1 proc' with linespoints 2, \
     'ompth_1_procs.dat' using 3:4\
     title 'Row OpenMP (threshold) - 1 proc' with linespoints 3

pause -1 'Press <Return> to compare data - row version - two procs'

plot 'omp_2_procs.dat' using 3:4\
     title 'Row OpenMP - 2 procs' with linespoints 1, \
     'ompth_2_procs.dat' using 3:4\
     title 'Row OpenMP (threshold) - 2 procs' with linespoints 2

pause -1 'Press <Return> to compare data - column version - single proc'

plot 'serial.dat' using 3:5\
     title 'Column - serial version' with linespoints 1, \
     'omp_1_procs.dat' using 3:5\
     title 'Column OpenMP - 1 proc' with linespoints 2, \
     'ompth_1_procs.dat' using 3:5\
     title 'Column OpenMP - 1 proc' with linespoints 3

pause -1 'Press <Return> to compare data - column version - two procs'

plot 'omp_2_procs.dat' using 3:5\
     title 'Column OpenMP - 2 procs' with linespoints 1, \
     'ompth_2_procs.dat' using 3:5\
     title 'Column OpenMP (threshold) - 2 procs' with linespoints 2

pause -1 'Press <Return> to stop'
