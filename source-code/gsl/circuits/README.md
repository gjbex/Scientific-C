# Circuits
The aim is to determine the resistance that will balance the Wheatstone
bridge.  Kirchhoff's laws are applied to obtain six linear equations
for the currents in te circuit.  The unknown resistance can be determined
either graphically, or by root finding.

## What is it?
1. `circuit_01.cc`: the program prints values for the unknown resistance,
    and the correspnding  current through the bridge resistor. 
    LU-decomposition is used to solve the set of equations.
1. `circuit_02.cc`: the program uses one-dimensional root finding to
    determine the resistance for which the current through the bridge
    is zero.  Note: illustrates how to mix C and C++ code.
1. `Makefile`: make file to build the applications.
1. `resistance.plt`: gnuplot script to show the current through the bridge
    versus the resistance.
1. `circuits.pptx`: Powerpoint presentation with the circuit and hints for
    solving the probem.
1. `circuit_01.c`: the program prints values for the unknown resistance,
    and the correspnding  current through the bridge resistor. 
    LU-decomposition is used to solve the set of equations.
1. `circuit_02.c`: the program uses one-dimensional root finding to
    determine the resistance for which the current through the bridge
    is zero.  
1. `Makefile.c_impl`: make file to build the C version of the
    applications.

## How to use?
The executables can be built using the make file, i.e.,
```bash
$ make
```
The current through the bridge can be computed as a function of the
unknown resistance can be computed using:
```bash
$ ./circuit_01.exe > resistance.txt
```
or simply:
```bash
$ make data
```
To plot the current, use:
```bash
$ ./resistance.plt
```

To use the C implementation, add the `f Makefile.c_impl` to the
`make` command.
