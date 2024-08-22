#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_vector.h>

void compute_center_of_mass(gsl_vector *x, gsl_vector *y,
                            double *cm_x, double *cm_y);
void compute_total_impulse(gsl_vector *v_x, gsl_vector *v_y,
                           double *cm_v_x, double *cm_v_y);
void compute_kinetic_energy(gsl_vector *v_x, gsl_vector *v_y,
                            gsl_vector_int *charge, double *E_kin);
void compute_potential_energy(gsl_vector *x, gsl_vector *y,
                              gsl_vector_int *charge, double *E_pot);

int main(int argc, char *argv[]) {
    int nr_particles = 10, particle_nr = 0;
    double cm_x, cm_y, cm_v_x, cm_v_y, E_kin, E_pot;
    double x, y, v_x, v_y;
    int charge;
    gsl_vector *x_vector, *y_vector, *v_x_vector, *v_y_vector;
    gsl_vector_int *charge_vector;
    if (argc > 1)
        nr_particles = atoi(argv[1]);
    x_vector = gsl_vector_alloc(nr_particles);
    y_vector = gsl_vector_alloc(nr_particles);
    v_x_vector = gsl_vector_alloc(nr_particles);
    v_y_vector = gsl_vector_alloc(nr_particles);
    charge_vector = gsl_vector_int_alloc(nr_particles);
    while (scanf("%lf %lf %lf %lf %d", &x, &y, &v_x, &v_y, &charge) > 0 &&
           particle_nr < nr_particles) {
        gsl_vector_set(x_vector, particle_nr, x);
        gsl_vector_set(y_vector, particle_nr, y);
        gsl_vector_set(v_x_vector, particle_nr, v_x);
        gsl_vector_set(v_y_vector, particle_nr, v_y);
        gsl_vector_int_set(charge_vector, particle_nr, charge);
        particle_nr++;
    }
    compute_center_of_mass(x_vector, y_vector, &cm_x, &cm_y);
    printf("center of mass = (%.6f, %.6f)\n", cm_x, cm_y);
    compute_total_impulse(v_x_vector, v_y_vector, &cm_v_x, &cm_v_y);
    printf("total impulse = (%.6lf, %.6lf)\n", cm_v_x, cm_v_y);
    compute_kinetic_energy(v_x_vector, v_y_vector, charge_vector, &E_kin);
    printf("kinetic energy = %.4e\n", E_kin);
    compute_potential_energy(x_vector, y_vector, charge_vector, &E_pot);
    printf("potential energy = %.4e\n", E_pot);
    gsl_vector_free(x_vector);
    gsl_vector_free(y_vector);
    gsl_vector_free(v_x_vector);
    gsl_vector_free(v_y_vector);
    gsl_vector_int_free(charge_vector);
    return EXIT_SUCCESS;
}

void compute_center_of_mass(gsl_vector *x, gsl_vector *y,
                            double *cm_x, double *cm_y) {
    int i;
    *cm_x = *cm_y = 0.0;
    for (i = 0; i < x->size; i++)
        *cm_x += gsl_vector_get(x, i);
    *cm_x /= x->size;
    for (i = 0; i < y->size; i++)
        *cm_y += gsl_vector_get(y, i);
    *cm_y /= y->size;
}

void compute_total_impulse(gsl_vector *v_x, gsl_vector *v_y,
                           double *cm_v_x, double *cm_v_y) {
    int i;
    *cm_v_x = *cm_v_y = 0.0;
    for (i = 0; i < v_x->size; i++)
        *cm_v_x += gsl_vector_get(v_x, i);
    *cm_v_x /= v_x->size;
    for (i = 0; i < v_y->size; i++)
        *cm_v_y += gsl_vector_get(v_y, i);
    *cm_v_y /= v_y->size;
}

void compute_kinetic_energy(gsl_vector *v_x, gsl_vector *v_y,
                            gsl_vector_int *charge, double *E_kin) {
    int i;
    const double m_e = 9.1094e-31, m_p = 1.6726e-27;
    *E_kin = 0.0;
    for (i = 0; i < v_x->size; i++) {
        double x_comp = gsl_vector_get(v_x, i);
        double y_comp = gsl_vector_get(v_y, i);
        int q = gsl_vector_int_get(charge, i);
        if (q > 0)
            *E_kin += 0.5*m_p*(x_comp*x_comp + y_comp*y_comp);
        else
            *E_kin += 0.5*m_e*(x_comp*x_comp + y_comp*y_comp);
    }
}

double compute_distance(gsl_vector *x, gsl_vector *y, int i, int j) {
    assert(x && y);
    assert(0 <= i && i < x->size);
    assert(0 <= j && j < x->size);
    double x1 = gsl_vector_get(x, i);
    double y1 = gsl_vector_get(y, i);
    double x2 = gsl_vector_get(x, j);
    double y2 = gsl_vector_get(y, j);
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void compute_potential_energy(gsl_vector *x, gsl_vector *y,
                              gsl_vector_int *charge, double *E_pot) {
    int i, j;
    const double q_e = 1.6022e-19;
    const double k_e = 8.9876e9;
    const double factor = k_e*q_e*q_e;
    *E_pot = 0.0;
    for (i = 0; i < x->size; i++) {
        int q1 = gsl_vector_int_get(charge, i);
        for (j = i + 1; j < x->size; j++) {
            int q2 = gsl_vector_int_get(charge, j);
            double r = compute_distance(x, y, i, j);
            if (fabs(r) > 1e-6)
                *E_pot += factor*q1*q2/r;
        }
    }
}
