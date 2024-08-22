#!/usr/bin/env gnuplot -persist

set xlabel "t (s)"
set ylabel "E (J)"
plot 'ode_trajectories.txt' using 1:12 with lines title "kinetic energy", \
     'ode_trajectories.txt' using 1:13 with lines title "potential energy"
