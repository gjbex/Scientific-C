#!/usr/bin/env gnuplot -persist

set xrange [0:2000]
set key off
set xlabel 'f'
plot 'power_spectrum1.txt' using 1:2 with lines
