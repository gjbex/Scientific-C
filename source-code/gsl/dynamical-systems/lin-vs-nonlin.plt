#!/usr/bin/env gnuplot -persist

set xlabel "t (s)"
set ylabel "theta"
plot 'linear.txt'  using 1:2  with lines title "linear oscillator", \
     'nonlinear.txt'   using 1:2  with lines title "nonlinear oscillator"
