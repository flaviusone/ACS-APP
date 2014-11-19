#-----------------------------------------------------------------------
# Sun Application Tuning Seminar
#
# Script to LAB performance data using GNU plot
#
# Ruud van der Pas - Sun Microsystems
#-----------------------------------------------------------------------

set grid
set title 'MXV performance: compiler optimized'
set xlabel 'Memory Footprint (KByte)'
set ylabel 'Performance (Mflop/s)'
set xrange [.25:524288]
set xtics .25,4,262144
set logscale x 2
set yrange [1:*]
set logscale y 2

plot 'serial.dat' using 3:4\
     title 'Row - compiler optimized' with linespoints 1, \
     'serial.dat' using 3:5\
     title 'Column - compiler optimized' with linespoints 2, \
     'serial.dat' using 3:6\
     title 'Library version' with linespoints 3

pause -1 'Press <Return> to compare performance - row version'

plot 'base.dat' using 3:4\
     title 'Row - not optimized' with linespoints 1, \
     'serial.dat' using 3:4\
     title 'Row - compiler optimized' with linespoints 2

pause -1 'Press <Return> to compare performance - column version'

plot 'base.dat' using 3:5\
     title 'Column - not optimized' with linespoints 1, \
     'serial.dat' using 3:5\
     title 'Column - compiler optimized' with linespoints 2

pause -1 'Press <Return> to stop'
