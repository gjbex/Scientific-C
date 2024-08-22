#include <assert.h>
#include <math.h>

#include "particles.h"

void particles_get(Particles *particles, int i,
                   double *x, double *y, double *v_x, double *v_y, int *q) {
    assert(0 <= i && i < particles->n);
    *x = gsl_vector_get(particles->x, i);
    *y = gsl_vector_get(particles->y, i);
    *v_x = gsl_vector_get(particles->v_x, i);
    *v_y = gsl_vector_get(particles->v_y, i);
    *q = gsl_vector_int_get(particles->q, i);
}

void particles_set(Particles *particles, int i,
                   double x, double y, double v_x, double v_y, int q) {
    assert(0 <= i && i < particles->n);
    gsl_vector_set(particles->x, i, x);
    gsl_vector_set(particles->y, i, y);
    gsl_vector_set(particles->v_x, i, v_x);
    gsl_vector_set(particles->v_y, i, v_y);
    gsl_vector_int_set(particles->q, i, q);
}

Particles *particles_alloc(int n) {
    Particles *particles;
    particles = (Particles *) malloc(sizeof(struct Particles_struct));
    particles->x = gsl_vector_alloc(n);
    particles->y = gsl_vector_alloc(n);
    particles->v_x = gsl_vector_alloc(n);
    particles->v_y = gsl_vector_alloc(n);
    particles->q = gsl_vector_int_alloc(n);
    particles->n = n;
    return particles;
}

void particles_free(Particles *particles) {
    gsl_vector_free(particles->x);
    gsl_vector_free(particles->y);
    gsl_vector_free(particles->v_x);
    gsl_vector_free(particles->v_y);
    gsl_vector_int_free(particles->q);
    free(particles);
}

void particles_fprintf(Particles *particles, FILE *fp, char *fmt) {
    int i;
    for (i = 0; i < particles->n; i++) {
        fprintf(fp, fmt,
                gsl_vector_get(particles->x, i),
                gsl_vector_get(particles->y, i),
                gsl_vector_get(particles->v_x, i),
                gsl_vector_get(particles->v_y, i),
                gsl_vector_int_get(particles->q, i));
    }
}

Particles *particles_fscanf(FILE *fp, int n) {
    double x, y, v_x, v_y;
    int q;
    int particle_nr = 0;
    Particles *particles = particles_alloc(n);
    while (fscanf(fp, "%lf %lf %lf %lf %d", &x, &y, &v_x, &v_y, &q) > 0 &&
           particle_nr < n) {
        particles_set(particles, particle_nr, x, y, v_x, v_y, q);
        particle_nr++;
    }
    particles->n = particle_nr;
    return particles;
}

void particles_move(Particles *particles, Particles *new_particles,
                    double delta_t) {
    const double factor = k_e*q_e*q_e;
    int i, j;
    for (i = 0; i < particles->n; i++) {
        double x_i, y_i, v_x_i, v_y_i, v_x_new_i, v_y_new_i;
        int q_i;
        double F_x_i = 0.0, F_y_i = 0.0;
        particles_get(particles, i, &x_i, &y_i, &v_x_i, &v_y_i, &q_i);
        for (j = 0; j < particles->n; j++) {
            double x_j, y_j, v_x_j, v_y_j, r_ij, F_ij;
            int q_j;
            if (i == j) continue;
            particles_get(particles, j, &x_j, &y_j, &v_x_j, &v_y_j, &q_j);
            r_ij = sqrt((x_i - x_j)*(x_i - x_j) + (y_i - y_j)*(y_i - y_j));
            F_ij = q_i*q_j*factor/(r_ij*r_ij*r_ij);
            F_x_i += F_ij*(x_i - x_j);
            F_y_i += F_ij*(y_i - y_j);
        }
        if (q_i > 0) {
            v_x_new_i = v_x_i + F_x_i*delta_t/m_p;
            v_y_new_i = v_y_i + F_y_i*delta_t/m_p;
        } else {
            v_x_new_i = v_x_i + F_x_i*delta_t/m_e;
            v_y_new_i = v_y_i + F_y_i*delta_t/m_e;
        }
        x_i += 0.5*(v_x_i + v_x_new_i)*delta_t;
        y_i += 0.5*(v_y_i + v_y_new_i)*delta_t;
        particles_set(new_particles, i,
                      x_i, y_i, v_x_new_i, v_y_new_i, q_i);
    }
}

void compute_center_of_mass(Particles *particles,
                            double *cm_x, double *cm_y) {
    int i;
    *cm_x = *cm_y = 0.0;
    for (i = 0; i < particles->n; i++)
        *cm_x += gsl_vector_get(particles->x, i);
    *cm_x /= particles->n;
    for (i = 0; i < particles->n; i++)
        *cm_y += gsl_vector_get(particles->y, i);
    *cm_y /= particles->n;
}

void compute_total_impulse(Particles *particles,
                           double *cm_v_x, double *cm_v_y) {
    int i;
    *cm_v_x = *cm_v_y = 0.0;
    for (i = 0; i < particles->n; i++)
        *cm_v_x += gsl_vector_get(particles->v_x, i);
    *cm_v_x /= particles->n;
    for (i = 0; i < particles->n; i++)
        *cm_v_y += gsl_vector_get(particles->v_y, i);
    *cm_v_y /= particles->n;
}

void compute_kinetic_energy(Particles *particles, double *E_kin) {
    int i;
    *E_kin = 0.0;
    for (i = 0; i < particles->n; i++) {
        double v_x = gsl_vector_get(particles->v_x, i);
        double v_y = gsl_vector_get(particles->v_y, i);
        int q = gsl_vector_int_get(particles->q, i);
        if (q > 0)
            *E_kin += 0.5*m_p*(v_x*v_x + v_y*v_y);
        else
            *E_kin += 0.5*m_e*(v_x*v_x + v_y*v_y);
    }
}

double compute_distance(Particles *particles, int i, int j) {
    assert(particles->x && particles->y);
    assert(0 <= i && i < particles->n);
    assert(0 <= j && j < particles->n);
    double x1 = gsl_vector_get(particles->x, i);
    double y1 = gsl_vector_get(particles->y, i);
    double x2 = gsl_vector_get(particles->x, j);
    double y2 = gsl_vector_get(particles->y, j);
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void compute_potential_energy(Particles *particles, double *E_pot) {
    int i, j;
    const double factor = k_e*q_e*q_e;
    *E_pot = 0.0;
    for (i = 0; i < particles->n; i++) {
        int q_i = gsl_vector_int_get(particles->q, i);
        for (j = i + 1; j < particles->n; j++) {
            int q_j = gsl_vector_int_get(particles->q, j);
            double r_ij = compute_distance(particles, i, j);
            *E_pot += factor*q_i*q_j/r_ij;
        }
    }
}
