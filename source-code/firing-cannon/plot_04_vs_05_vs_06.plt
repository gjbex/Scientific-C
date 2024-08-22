#!/usr/bin/gnuplot -persist

set xlabel "x"
set ylabel "y"
plot "corrected.txt" using 2:3 smooth bezier title 'no air drag', \
     "air_drag.txt" using 2:3 smooth bezier title 'with air drag', \
     "density.txt" using 2:3 smooth bezier title 'air density corrected'
