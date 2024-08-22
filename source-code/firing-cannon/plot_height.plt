#!/usr/bin/gnuplot -persist

set xlabel 'alpha'
set ylabel 'max. height'
unset key

plot 'range.txt' using 1:3 with lines
