#include <stdlib.h>
#include "particles.h"

int main(int argc, char *argv[]) {
    Particles *particles, *new_particles, *tmp;
    int nr_particles = 10, nr_iters = 10, iter_nr;
    double E_kin, E_pot, E_tot, E_0, t = 0.0, t_max = 3.0e-14, delta_t;
    if (argc > 1)
        nr_particles = atoi(argv[1]);
    if (argc > 2)
        nr_iters = atoi(argv[2]);
    particles = particles_fscanf(stdin, nr_particles);
    printf("%.12le ", t);
    particles_fprintf(particles, stdout,
                      "%.12le %.12le %.12le %.12le %d ");
    compute_kinetic_energy(particles, &E_kin);
    compute_potential_energy(particles, &E_pot);
    E_0 = E_kin + E_pot;
    printf(" %.12le %.12le %.12le %.12le\n", E_kin, E_pot, E_0, 0.0);
    new_particles = particles_alloc(nr_particles);
    delta_t = t_max/nr_iters;
    for (iter_nr = 0; iter_nr < nr_iters; iter_nr++) {
        particles_move(particles, new_particles, delta_t);
        tmp = particles;
        particles = new_particles;
        new_particles = tmp;
        t += delta_t;
        printf("%.12le ", t);
        particles_fprintf(particles, stdout,
                          "%.12le %.12le %.12le %.12le %d ");
        compute_kinetic_energy(particles, &E_kin);
        compute_potential_energy(particles, &E_pot);
        E_tot = E_kin + E_pot;
        printf(" %.12le %.12le %.12le %.12le\n",
               E_kin, E_pot, E_tot, (E_tot - E_0)/E_0);
    }
    particles_free(particles);
    particles_free(new_particles);
    return EXIT_SUCCESS;
}
