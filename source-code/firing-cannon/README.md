# Firing cannons

We consider firing a cannon.  The initial velocity of the projectile is
fixed, the elevation can be modified.  We compute the position of the
projectile for time steps with a fixed delta value.

## What is it?
1. `cannon_01.c`: computation of position and velocity of the projectile
    based on the analytic solution of the equations of motion.  The program
    prints the time, x and y position, x and y component of the velocity.
1. `cannon_02.c`: computation of the position and velocity of the
    projectile based on the Euler method to solve the equations of motion.
    The program prints the time, x and y position, x and y component of
    the velocity.
1. `cannon_03.c`: in addition to `cannon_02.c`, this version also prints
    the total energy at each time step.
1. `cannon_04.c`: here, the Euler method has been correcto to ensure that
    the law of conservation of energy is respected.
1. `cannon_05.c`: added effect or air drag on projectile.
1. `cannon_06.c`: added effect or air drag on projectile, taking into
    account air density.
1. `cannon_ode.c`: solving the differential equation using GSL's RKF(4. 5)
1. `cannon_max_range.c`: computes the maximal range of the cannon.
1. `Makefile`: make file to build the C programs.
1. `plot_01.plt`: gnuplot file to plot the trajectory of the projectile as
    computed by `cannon_01.c`.
1. `plot_02.plt`: gnuplot file to plot the trajectory of the projectile as
    computed by `cannon_02.c`.
1. `plot_01_vs_02.plt`: gnuplot file to plot the trajectory of the
    projectile as computed by `cannon_02.c` versus that by `cannon_02.c`..
1. `plot_03.plt`: gnuplot file to plot the energy as function of  time as
    computed by `cannon_03.c`.
1. `plot_01_vs_04.plt`: gnuplot file to plot the trajectory of the
    projectile as computed by `cannon_04.c` versus that by `cannon_02.c`..
1. `plot_04_vs_05.plt`: gnuplot file to visualize the effect of air drag.
1. `plot_04_vs_05_vs_06.plt`: gnuplot file to visualize the effect of air
    drag, and the effect of correction for air density.
1. `plot_06_vs_ode.plt`: gnuplot script to compare corrected Euler method
    with RKF(4, 5).
1. `firing_cannon.pptx`: Powerpoint slides explaining the exercise.

## How to use?
Simply run make with the `data` target, i.e.,
```bash
$ make data
```
Visualize using the gnuplot scripts.

## Requirements
gnuplot (version 4.6) is used for visualization.
