#!/usr/bin/gnuplot -persist

set logscale x
set key left top
set xrange [10.0: 20000.0]

plot 'entropy_constrained.txt' \
        using 1:2 \
        with lines \
        title 'constrained',  \
     'entropy_unconstrained.txt' \
        using 1:2 \
        with lines \
        title 'unconstrained'
