#!/usr/bin/gnuplot -persist

unset key
set xlabel 'n'
set ylabel 'abs(z)'
set logscale y

plot 'non_conv.txt' using 1:2 with lines
