# PowerSpectrums
Signal analysis by computing the power spectrum using the GSL's FFT
function.

## What is it?
1. `signal.py`: Python script to generate a signal
1. `power_spectrum.c`: copmutes the power spectrum of a given signal file.
1. `Makefile`: make file to build the C application.
1. `signal1.plt`: gnuplot script to visualize signal 1.
1. `signal2.plt`: gnuplot script to visualize signal 2.
1. `power_spectrum1.plt`: gnuplot script to visualize power spectrum of
    signal 1.
1. `power_spectrum2.plt`: gnuplot script to visualize power spectrum of
    signal 2.
1. `example_signal.plt`: gnuplot script to visualize example signal.
1. `example_spectrum.plt`: gnuplot script to visualize power spectrum of
    example signal.

## How to use?
Use `make data` to create data signals and power spectrums.
