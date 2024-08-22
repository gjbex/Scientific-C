#include <stdio.h>
#include <stdlib.h>

#include "particles.h"

int main(int argc, char *argv[]) {
    Particles *particles;
    int nr_particles = 10;
    double cm_x, cm_y, cm_v_x, cm_v_y, E_kin, E_pot;
    if (argc > 1)
        nr_particles = atoi(argv[1]);
    particles = particles_fscanf(stdin, nr_particles);
    compute_center_of_mass(particles, &cm_x, &cm_y);
    printf("center of mass = (%.12le, %.12le)\n", cm_x, cm_y);
    compute_total_impulse(particles, &cm_v_x, &cm_v_y);
    printf("total impulse = (%.12le, %.12le)\n", cm_v_x, cm_v_y);
    compute_kinetic_energy(particles, &E_kin);
    printf("kinetic energy = %.12le\n", E_kin);
    compute_potential_energy(particles, &E_pot);
    printf("potential energy = %.12le\n", E_pot);
    particles_free(particles);
    return EXIT_SUCCESS;
}
