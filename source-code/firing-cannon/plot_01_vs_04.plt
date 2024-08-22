#!/usr/bin/gnuplot -persist

set xlabel "x"
set ylabel "y"
plot "corrected.txt" using 2:3 smooth bezier title 'corrected solution', \
     "analytic.txt" using 2:3 smooth bezier title 'analytic solution'
