#!/usr/bin/gnuplot -persist

set xlabel "t"
set ylabel "E(t)"
set yrange [244990.0:245040.6]
unset key
plot "energy.txt" using 1:6 smooth bezier
