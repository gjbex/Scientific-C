#!/usr/bin/gnuplot -persist

set xlabel "x"
set ylabel "y"
plot "density.txt" using 2:3 smooth bezier title 'corrected Euler', \
     "ode.txt" using 2:3 smooth bezier title 'RKF(4, 5)'
