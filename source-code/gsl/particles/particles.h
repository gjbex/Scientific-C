#ifndef _PARTICLES_HDR_
#define _PARTICLES_HDR_

#include <stdio.h>
#include <gsl/gsl_vector.h>

static const double m_e = 9.1094e-31; /* electron mass in kg */
static const double m_p = 1.6726e-27; /* proton mass in kg */
static const double q_e = 1.6022e-19; /* electron charge in C */
static const double k_e = 8.9876e9;   /* Coulomb's constant in Nm^2/C^2 */

typedef struct Particles_struct {
    gsl_vector *x, *y, *v_x, *v_y;
    gsl_vector_int *q;
    int n;
} Particles;

Particles *particles_alloc(int n);
void particles_free(Particles *particles);
void particles_fprintf(Particles *particles, FILE *fp, char *fmt);
Particles *particles_fscanf(FILE *fp, int n);
void compute_center_of_mass(Particles *particles,
                            double *cm_x, double *cm_y);
void compute_total_impulse(Particles *particles,
                           double *cm_v_x, double *cm_v_y);
void compute_kinetic_energy(Particles *particles, double *E_kin);
double compute_distance(Particles *particles, int i, int j);
void compute_potential_energy(Particles *particles, double *E_pot);

#endif
