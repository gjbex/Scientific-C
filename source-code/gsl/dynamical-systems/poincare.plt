#!/usr/bin/env gnuplot -persist

set xlabel "theta)"
set ylabel "omega"
set key off
plot 'poincare_chaos.txt'   using 2:3  with dots title "chaotic regime"
