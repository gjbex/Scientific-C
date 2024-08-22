#!/usr/bin/env gnuplot -persist

set xlabel "t (s)"
set ylabel "(E_0 - E_total)/E_0"
set key off
plot 'trajectories_10.txt' using 1:55 with lines
