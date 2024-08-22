#!/usr/bin/gnuplot -persist

set xlabel 'alpha'
set ylabel 'range'
unset key

plot 'range.txt' using 1:2 with lines
