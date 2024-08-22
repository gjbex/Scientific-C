#!/usr/bin/env gnuplot -persist

set xlabel "x (m)"
set ylabel "y (m)"
plot 'ode_trajectories.txt' using 2:3 with lines title "electron 1, ODE", \
     'ode_trajectories.txt' using 7:8 with lines title "electron 2, ODE", \
     'trajectories.txt' using 2:3 with lines title "electron 1", \
     'trajectories.txt' using 7:8 with lines title "electron 2"
