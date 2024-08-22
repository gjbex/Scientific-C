#!/usr/bin/env gnuplot -persist

set xrange [0:0.02]
set key off
set xlabel 't'
set ylabel 'theta'
plot 'signal2.txt' using 1:2 with lines
