#!/usr/bin/gnuplot -persist

set xlabel "x"
set ylabel "y"
set xrange [45400.0:45425.0]
plot "euler.txt" using 2:3 smooth bezier title 'Euler solution', \
     "analytic.txt" using 2:3 smooth bezier title 'analytic solution'
