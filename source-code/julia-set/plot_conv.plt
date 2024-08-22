#!/usr/bin/gnuplot -persist

unset key
set xlabel 'n'
set ylabel 'abs(z)'

plot 'conv.txt' using 1:2 with lines
