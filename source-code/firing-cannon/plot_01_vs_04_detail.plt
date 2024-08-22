#!/usr/bin/gnuplot -persist

set xlabel "x"
set ylabel "y"
set xrange [45400.0:45425.0]
plot "corrected.txt" using 2:3 smooth bezier title 'corrected solution', \
     "analytic.txt" using 2:3 smooth bezier title 'analytic solution'
