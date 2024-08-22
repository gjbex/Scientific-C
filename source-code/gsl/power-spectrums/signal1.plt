#!/usr/bin/env gnuplot -persist

set xrange [0:0.1]
set key off
set xlabel 't'
set ylabel 'theta'
plot 'signal1.txt' using 1:2 with lines
