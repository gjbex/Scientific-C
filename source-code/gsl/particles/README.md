# Particles
Here, a many body problem is considered, consisting of charged particles
with given initial position and velocity in two dimensions.

## What is it?
1. `generate_particles.c`: generate a given number of particles, i.e.,
    for each particle, a position is drawn from a chi square distribution,
    its velocity from a Maxwell-Bolzmann distribution, and its charge is
    +/- 1 with equal probability.
1. `compute_properties_01.c`: computes the center of mass and the total
    impulse of the particles, as well as the total energy.
1. `particles.h`: declaration/definition of constants, data types and
    functions to represent charged particles for simulation.
1. `particles.c`: definition of functions to represent charged particles
    for simulation.
1. `compute_properties_02.c`: refactored version that uses the particles
    functionality in `particles.[ch]`.
1. `dynamics.c`: straightforware n-body dynamics code.
1. `ode.c`: dynamics is computed using RKF(4, 5) ODE solver.
1. `two_particles.txt`: initial configuration of two electrons moving
    towards one another.
1. `two_particles_ode_trajectories.plt` gnuplot script to plot the
    trajectories of the two particles as computed using `ode.exe`.
1. `two_particles_ode_energies.plt` gnuplot script to plot the
    kinetic and potential energy of the two particles as computed using
    `ode.exe`.
1. `two_particles_ode_conservation.plt` gnuplot script to plot the
    the relative difference between the  total energy and the initial
    energy as computed by `ode.exe`.  This is a check to see whether
    energy is conserved (as it should be).
1. `two_particles_energies.plt` gnuplot script to plot the
    kinetic and potential energy of the two particles as computed using
    `dynamics.exe`.
1. `two_particles_conservation.plt` gnuplot script to plot the
    the relative difference between the  total energy and the initial
    energy as computed by `dynamics.exe`.  This is a check to see whether
    energy is conserved (as it should be).
1. `two_particles_cmp_trajectories.plt`: gnuplot script to plot the
    particle trajectories as computed by `dynamics.exe` versus `ode.exe`.
1. `two_particles_cmp_energies.plt`: gnuplot script to plot the
    particles' kinetic and potential energy as computed by `dynamics.exe`
    versus `ode.exe`.
1. `trajectories_10.plt`: `ode.exe` run on 10 particles.
1. `ten_particles_trajectories.plt` gnuplot script to plot the
    trajectories of the ten particles as computed using `ode.exe`.
1. `ten_particles_energies.plt` gnuplot script to plot the
    kinetic and potential energy of the ten particles as computed using
    `ode.exe`.
1. `ten_particles_conservation.plt` gnuplot script to plot the
    the relative difference between the  total energy and the initial
    energy as computed by `ode.exe`.  This is a check to see whether
    energy is conserved (as it should be).
1. `timings.txt`: scaling of `ode.exe` with the number of particles.
1. `Makefile`: make file to build the executables. 

## How to use?
To compute the two-particle trajectories, either use `dynamics.exe` or
`ode.exe`:
```bash
$ ./dynamics.exe 2 1000 < two_particles.txt > trajectories.txt
```
```bash
$ ./ode.exe 2 1000 < two_particles.txt > ode_trajectories.txt
```
Here, 2 is the number of particles, and 1000 is the number of iterations
for the simulations.
For simplicity, there is a make rule to run the simulations, i.e.,
```bash
$ make data
```
All `.plt` files are executable, and rely on the existence of both
`trajectories.txt` and `ode_trajectories.txt`, e.g.,
```bash
$ ./two_particles_ode_trajectories.plt
```

## Requirements
* The GNU Scientific Library is used for data representation and
    computations (version 1.16 or more recent).
* The visualizatin scripts use gnuplot (version 4.6).
