#!/usr/bin/env gnuplot -persist

set xlabel "x (m)"
set ylabel "y (m)"
plot 'ode_trajectories.txt' using 2:3 with lines title "electron 1", \
     'ode_trajectories.txt' using 7:8 with lines title "electron 2"
