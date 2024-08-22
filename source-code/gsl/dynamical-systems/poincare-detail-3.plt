#!/usr/bin/env gnuplot -persist

set xrange [-1.23:-1.19] 
set yrange [0.042:0.055]
set xlabel "theta)"
set ylabel "omega"
set key off
plot 'poincare_chaos.txt'   using 2:3  with dots title "chaotic regime"
