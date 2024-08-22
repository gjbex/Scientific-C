#!/usr/bin/env gnuplot -persist

set xrange [2.15:2.20]
set yrange [-1.3:-1.24]
set xlabel "theta)"
set ylabel "omega"
set key off
plot 'poincare_chaos.txt'   using 2:3  with dots title "chaotic regime"
