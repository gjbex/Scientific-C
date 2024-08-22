#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

#include "particles.h"

void convert_from_particles(Particles *particles, double **var);
void convert_to_particles(Particles *particles, double *var);
int func(double t, const double y[], double f[], void *params);

int main(int argc, char *argv[]) {
    int iter_nr, nr_iters = 1000;
    int nr_particles = argc > 1 ? atoi(argv[1]) : 10;
    Particles *particles = particles_fscanf(stdin, nr_particles);
    double E_kin, E_pot, E_tot, E_0;
    gsl_odeiv2_system sys = {func, NULL, 4*particles->n, particles};
    gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(
            &sys, gsl_odeiv2_step_rkf45, 1.0e-6, 1.0e-6, 0.0
    );
    double t = 0.0, t_max = 3.0e-14;
    double *y;
    convert_from_particles(particles, &y);
    printf("%.12le ", t);
    particles_fprintf(particles, stdout,
                      "%.12le %.12le %.12le %.12le %d ");
    compute_kinetic_energy(particles, &E_kin);
    compute_potential_energy(particles, &E_pot);
    E_tot = E_kin + E_pot;
    E_0 = E_tot;
    printf(" %.12le %.12le %.12le %.12le\n",
           E_kin, E_pot, E_tot, (E_tot - E_0)/E_0);
    for (iter_nr = 1; iter_nr < nr_iters; iter_nr++) {
        double ti = iter_nr*t_max/nr_iters;
        int status = gsl_odeiv2_driver_apply(driver, &t, ti, y);
        if (status != GSL_SUCCESS) {
            fprintf(stderr, "error code %d\n", status);
            break;
        }
        convert_to_particles(particles, y);
        printf("%.12le ", t);
        particles_fprintf(particles, stdout,
                          "%.12le %.12le %.12le %.12le %d ");
        compute_kinetic_energy(particles, &E_kin);
        compute_potential_energy(particles, &E_pot);
        E_tot = E_kin + E_pot;
        printf(" %.12le %.12le %.12le %.12le\n",
               E_kin, E_pot, E_tot, (E_tot - E_0)/E_0);
    } 
    gsl_odeiv2_driver_free(driver);
    free(y);
    return EXIT_SUCCESS;
}

double distance(const double y[], int i, int j) {
    double x_i, y_i, x_j, y_j;
    x_i = y[i*4];
    y_i = y[i*4 + 1];
    x_j = y[j*4];
    y_j = y[j*4 + 1];
    return sqrt((x_i - x_j)*(x_i - x_j) + (y_i - y_j)*(y_i - y_j));
}

int func(double t, const double y[], double f[], void *params) {
    const double factor = k_e*q_e*q_e;
    int particle_nr, i;
    Particles *particles = (Particles *) params;
    for (particle_nr = 0; particle_nr < particles->n; particle_nr++) {
        int q = gsl_vector_int_get(particles->q, particle_nr);
        double F_x = 0.0, F_y = 0.0;
        for (i = 0; i < particles->n; i++) {
            int q_i = gsl_vector_int_get(particles->q, i);
            double r = distance(y, particle_nr, i);
            double x_i = y[i*4], y_i = y[i*4 + 1];
            if (i == particle_nr) continue;
            F_x += q_i*(y[particle_nr*4] - x_i)/(r*r*r);
            F_y += q_i*(y[particle_nr*4 + 1] - y_i)/(r*r*r);
        }
        F_x *= factor*q;
        F_y *= factor*q;
        if (q > 0) {
            f[particle_nr*4 + 2] = F_x/m_p;
            f[particle_nr*4 + 3] = F_y/m_p;
        } else {
            f[particle_nr*4 + 2] = F_x/m_e;
            f[particle_nr*4 + 3] = F_y/m_e;
        }
        f[particle_nr*4] = y[particle_nr*4 + 2];
        f[particle_nr*4 + 1] = y[particle_nr*4 + 3];
    }
    return GSL_SUCCESS;
}

void convert_from_particles(Particles *particles, double **var) {
    int particle_nr;
    *var = (double *) malloc(4*particles->n*sizeof(double));
    for (particle_nr = 0; particle_nr < particles->n; particle_nr++) {
        double x, y, v_x, v_y;
        int q;
        particles_get(particles, particle_nr, &x, &y, &v_x, &v_y, &q);
        (*var)[particle_nr*4 + 0] = x;
        (*var)[particle_nr*4 + 1] = y;
        (*var)[particle_nr*4 + 2] = v_x;
        (*var)[particle_nr*4 + 3] = v_y;
    }
}

void convert_to_particles(Particles *particles, double *var) {
    int particle_nr;
    for (particle_nr = 0; particle_nr < particles->n; particle_nr++) {
        int q = gsl_vector_int_get(particles->q, particle_nr);
        particles_set(particles, particle_nr,
                      var[particle_nr*4 + 0],
                      var[particle_nr*4 + 1],
                      var[particle_nr*4 + 2],
                      var[particle_nr*4 + 3],
                      q);
    }
}
