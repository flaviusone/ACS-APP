#-----------------------------------------------------------------------
# Sun Application Tuning Seminar
#
# Script to LAB performance data using GNU plot
#
# Ruud van der Pas - Sun Microsystems
#-----------------------------------------------------------------------

set grid
set title 'MXV performance: automatically parallelized version (optimized for First Touch)'
set xlabel 'Memory Footprint (KByte)'
set ylabel 'Performance (Mflop/s)'
set xrange [.25:524288]
set xtics .25,4,262144
set logscale x 2
set yrange [1:*]

plot 'parft_1_procs.dat' using 3:4\
     title 'Row Autopar (first touch) - 1 proc' with linespoints 1, \
     'parft_2_procs.dat' using 3:4\
     title 'Row Autopar (first touch) - 2 procs' with linespoints 2

pause -1 'Press <Return> to plot data for the column version'

plot 'parft_1_procs.dat' using 3:5\
     title 'Column Autopar (first touch) - 1 proc' with linespoints 1, \
     'parft_2_procs.dat' using 3:5\
     title 'Column Autopar (first touch) - 2 procs' with linespoints 2

pause -1 'Press <Return> to plot data for the PerfLib version'

plot 'parft_1_procs.dat' using 3:6\
     title 'Library version (first touch) - 1 proc' with linespoints 1, \
     'parft_2_procs.dat' using 3:6\
     title 'Library version (first touch) - 2 procs' with linespoints 2

pause -1 'Press <Return> to compare data - row version - single proc'

plot 'serial.dat' using 3:4\
     title 'Row - serial version' with linespoints 1, \
     'par_1_procs.dat' using 3:4\
     title 'Row Autopar - 1 proc' with linespoints 2, \
     'parft_1_procs.dat' using 3:4\
     title 'Row Autopar (first touch) - 1 proc' with linespoints 3

pause -1 'Press <Return> to compare data - row version - two procs'

plot 'par_2_procs.dat' using 3:4\
     title 'Row Autopar - 2 procs' with linespoints 1, \
     'parft_2_procs.dat' using 3:4\
     title 'Row Autopar (first touch) - 2 procs' with linespoints 2

pause -1 'Press <Return> to compare data - column version - single proc'

plot 'serial.dat' using 3:5\
     title 'Column - serial version' with linespoints 1, \
     'par_1_procs.dat' using 3:5\
     title 'Column Autopar - 1 proc' with linespoints 2, \
     'parft_1_procs.dat' using 3:5\
     title 'Column Autopar (first touch) - 1 proc' with linespoints 3

pause -1 'Press <Return> to compare data - column version - two procs'

plot 'par_2_procs.dat' using 3:5\
     title 'Column Autopar - 2 procs' with linespoints 1, \
     'parft_2_procs.dat' using 3:5\
     title 'Column Autopar (first touch) - 2 procs' with linespoints 2

pause -1 'Press <Return> to compare data - library version - single proc'

plot 'par_1_procs.dat' using 3:6\
     title 'Library version - 1 proc' with linespoints 1, \
     'parft_1_procs.dat' using 3:6\
     title 'Library version (first touch) - 1 proc' with linespoints 2

pause -1 'Press <Return> to compare data - library version - two procs'

plot 'par_2_procs.dat' using 3:6\
     title 'Library version - 2 procs' with linespoints 1, \
     'parft_2_procs.dat' using 3:6\
     title 'Library version (first touch) - 2 procs' with linespoints 2

pause -1 'Press <Return> to stop'
