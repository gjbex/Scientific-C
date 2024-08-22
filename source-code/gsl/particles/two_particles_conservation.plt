#!/usr/bin/env gnuplot -persist

set xlabel "t (s)"
set ylabel "(E_0 - E_total)/E_0"
set key off
plot 'trajectories.txt' using 1:15 with lines
