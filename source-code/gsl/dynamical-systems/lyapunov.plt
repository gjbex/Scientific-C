#!/usr/bin/env gnuplot -persist

set xlabel "t (s)"
set ylabel "difference"
set logscale y
plot 'lyapunov_normal.txt'  using 1:2  with lines title "normal regime", \
     'lyapunov_chaos.txt'   using 1:2  with lines title "chaotic regime"
