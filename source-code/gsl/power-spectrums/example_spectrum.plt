#!/usr/bin/env gnuplot -persist

set xrange [400:500]
set key off
set xlabel 'f'
plot 'example_spectrum.txt' using 1:2 with lines
