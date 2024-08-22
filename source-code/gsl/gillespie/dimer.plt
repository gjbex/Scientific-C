#!/usr/bin/gnuplot -persist

set key right center

plot 'dimer.txt' using 1:2 with lines title 'A molecules', \
     'dimer.txt' using 1:4 with lines title 'AB molecules'
