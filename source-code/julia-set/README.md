# Julia
Compute and visualize the Julia fractal.

## What is it?
1. `julia.c`: C99 code to compute the Julia set, takes the resolution
    as an optional input (same for x and y dimensions), and prints a
    matrix containing the resulting matrix as output.
1. `Makefile`: make file to build and execute the code.
1. `plot_julia.plt`: gnuplot script to present data as a heatmap.
1. `julia_iterate.c`: C99 code to iterate the function starting from a
    specific complex number for the given number of iterations.  The
    complex number is specified as its real and imaginary part.
1. `plot_conv.plt`: gnuplot script to plot an example of a function
    iteration that doesn't (immediately) diverge.
1. `plot_non_conv.plt`: gnuplot script to plot an example of a function
    iteration that diverges.
