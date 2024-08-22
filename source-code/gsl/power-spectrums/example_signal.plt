#!/usr/bin/env gnuplot -persist

set xrange [0:0.18]
set key off
set xlabel 't'
set ylabel 'theta'
plot 'example_signal.txt' using 1:2 with lines
