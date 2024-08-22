#!/usr/bin/env gnuplot -persist

set xlabel "t (s)"
set ylabel "E (J)"
plot 'trajectories_10.txt' using 1:52 with lines title "kinetic energy", \
     'trajectories_10.txt' using 1:53 with lines title "potential energy"
