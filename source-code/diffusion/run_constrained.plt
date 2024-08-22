#!/usr/bin/gnuplot -persist

plot 'very_short_run_constrained.txt' \
        using 1:2 \
        with lines \
        title '200 steps',  \
     'short_run_constrained.txt' \
        using 1:2 \
        with lines \
        title '200 steps',  \
     'medium_run_constrained.txt' \
        using 1:2 \
        with lines \
        title '2000 steps', \
     'long_run_constrained.txt' \
        using 1:2 \
        with lines \
        title '20000 steps'
