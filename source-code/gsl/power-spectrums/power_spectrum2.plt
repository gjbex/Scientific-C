#!/usr/bin/env gnuplot -persist

set xrange [0:1000]
set key off
set xlabel 'f'
set logscale y
plot 'power_spectrum2.txt' using 1:2 with lines
