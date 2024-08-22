#!/usr/bin/gnuplot -persist

set xlabel "x"
set ylabel "y"
unset key
plot "analytic.txt" using 2:3 smooth bezier
