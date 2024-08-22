#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

#include "cl_params.h"

int eqns(double t, const double y[], double f[], void *params);
int jacobian(double t, const double y[], double *dfdy, double *dfdt,
             void *params);

int main(int argc, char *argv[]) {
    Params params;
    initCL(&params);
    if (argc > 1) {
        if (access(argv[1], R_OK) != -1) {
            parseFileCL(&params, argv[1]);
        } else {
            parseCL(&params, &argc, &argv);
        }
    }
    if (params.verbose)
        dumpCL(stdout, "# ", &params);
    const gsl_odeiv_step_type *T = gsl_odeiv_step_rk4;
    gsl_odeiv_step *s = gsl_odeiv_step_alloc(T, 2);
    gsl_odeiv_control *c = gsl_odeiv_control_y_new(1e-6, 0.0);
    gsl_odeiv_evolve *e = gsl_odeiv_evolve_alloc(2);
    gsl_odeiv_system sys = {eqns, jacobian, 2, &params};
    double t = params.start_t;
    double h = 1e-10;
    double y[2] = {params.omega_0, params.theta_0};
    printf("# t theta omega\n");
    printf ("%.5e %.15e %.15e\n", t, y[1], y[0]);
    while (t < params.end_t) {
        int status = gsl_odeiv_evolve_apply (e, c, s,
                &sys, 
                &t, params.end_t,
                &h, y);
        if (status != GSL_SUCCESS)
            break;
        printf ("%.5e %.15e %.15e\n", t, y[1], y[0]);
    }
    gsl_odeiv_evolve_free (e);
    gsl_odeiv_control_free (c);
    gsl_odeiv_step_free (s);
    finalizeCL(&params);
    return EXIT_SUCCESS;
}

int eqns(double t, const double y[], double f[], void *params) {
    double g = ((Params *) params)->g;
    double l = ((Params *) params)->l;
    double q = ((Params *) params)->q;
    double F_D = ((Params *) params)->F_D;
    double Omega_D = ((Params *) params)->Omega_D;
    f[0] = -(g/l)*sin(y[1]) - q*y[0] + F_D*sin(Omega_D*t);
    f[1] = y[0];
    return GSL_SUCCESS;
}

int jacobian(double t, const double y[], double *dfdy, double *dfdt,
        void *params) {
    double g = ((Params *) params)->g;
    double l = ((Params *) params)->l;
    double q = ((Params *) params)->q;
    double F_D = ((Params *) params)->F_D;
    double Omega_D = ((Params *) params)->Omega_D;
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdt, 2, 2);
    gsl_matrix *m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, -q);
    gsl_matrix_set(m, 0, 1, -g*cos(y[1])/l);
    gsl_matrix_set(m, 1, 0, 1.0);
    gsl_matrix_set(m, 1, 1, 0.0);
    dfdt[0] = F_D*Omega_D*cos(Omega_D*t);
    dfdt[1] = 0.0;
    return GSL_SUCCESS;
}

