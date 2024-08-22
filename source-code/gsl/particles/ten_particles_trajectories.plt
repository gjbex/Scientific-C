#!/usr/bin/env gnuplot -persist

set xlabel "x (m)"
set ylabel "y (m)"
set key off
plot 'trajectories_10.txt'  using 2:3  with lines title "electron 1", \
     'trajectories_10.txt'  using 7:8  with lines title "electron 2", \
     'trajectories_10.txt' using 12:13 with lines title "electron 3", \
     'trajectories_10.txt' using 17:18 with lines title "electron 4", \
     'trajectories_10.txt' using 22:23 with lines title "electron 5", \
     'trajectories_10.txt' using 27:28 with lines title "electron 6", \
     'trajectories_10.txt' using 32:33 with lines title "electron 7", \
     'trajectories_10.txt' using 37:38 with lines title "electron 8", \
     'trajectories_10.txt' using 42:43 with lines title "electron 9", \
     'trajectories_10.txt' using 47:48 with lines title "electron 10"
