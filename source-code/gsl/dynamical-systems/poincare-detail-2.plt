#!/usr/bin/env gnuplot -persist

set xrange [-1.3:-0.9]
set yrange [0.03:0.15]
set xlabel "theta)"
set ylabel "omega"
set key off
plot 'poincare_chaos.txt'   using 2:3  with dots title "chaotic regime"
