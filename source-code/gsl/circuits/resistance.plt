#!/usr/bin/gnuplot -persist

set xlabel "resistance (Ohm)"
set ylabel "current (A)"
set yrange [-0.01:0.01]
set key off
plot 'resistance.txt' using 1:2 with lines, \
     0 with lines
