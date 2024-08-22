#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

#include "cl_params.h"

const double Pi = 3.14159265359;

int eqns(double t, const double y[], double f[], void *params);
int jacobian(double t, const double y[], double *dfdy, double *dfdt,
             void *params);
double clip(double omega);

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
    double t, y[2];
    long step;
    t    = 0.0;
    y[0] = params.theta_0;
    y[1] = params.omega_0;
    gsl_odeiv2_system sys = {eqns, jacobian, 2, &params};
    gsl_odeiv2_driver *driver
        = gsl_odeiv2_driver_alloc_standard_new(&sys,
                                               gsl_odeiv2_step_rkf45,
                                               params.delta_t,
                                               params.tol, 0.0,
                                               1.0, 1.0);
    printf("# t theta omega\n");
    printf("%.8f %.8f %.8f\n", t, y[0], y[1]);
    for (step = 1; step < params.nr_steps; step++) {
        double tLim = 2.0*step*Pi/params.Omega_D;
        int status = gsl_odeiv2_driver_apply(driver, &t, tLim, y);
        if (status != GSL_SUCCESS) {
            fprintf(stderr, "### warning: step %lf not succesful\n", t);
            break;
        }
        printf("%.8f %.8f %.8f\n", t, clip(y[0]), y[1]);
    }
    gsl_odeiv2_driver_free(driver);
    finalizeCL(&params);
    return EXIT_SUCCESS;
}

int eqns(double t, const double y[], double f[], void *params) {
    double g = ((Params *) params)->g;
    double l = ((Params *) params)->l;
    double q = ((Params *) params)->q;
    double F_D = ((Params *) params)->F_D;
    double Omega_D = ((Params *) params)->Omega_D;
    f[0] = y[1];
    f[1] = -(g/l)*sin(y[0]);
    f[1] = f[1] - q*y[1] + F_D*sin(Omega_D*t);
    return GSL_SUCCESS;
}

int jacobian(double t, const double y[], double *dfdy, double *dfdt,
        void *params) {
    double g = ((Params *) params)->g;
    double l = ((Params *) params)->l;
    double q = ((Params *) params)->q;
    double F_D = ((Params *) params)->F_D;
    double Omega_D = ((Params *) params)->Omega_D;
    gsl_matrix_view dfdy_mat;
    gsl_matrix *m;
    dfdy_mat = gsl_matrix_view_array(dfdt, 2, 2);
    m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, 0.0);
    gsl_matrix_set(m, 0, 1, 1.0);
    gsl_matrix_set(m, 1, 0, -(g/l)*cos(y[0]));
    gsl_matrix_set(m, 1, 1, -q);
    dfdt[0] = 0.0;
    dfdt[1] = F_D*Omega_D*cos(Omega_D*t);
    return GSL_SUCCESS;
}

double clip(double omega) {
    if (omega > 2.0*Pi) {
        double n = floor(omega/(2.0*Pi));
        return omega - 2.0*n*Pi;
    } else if (omega < 0.0) {
        double n = ceil(fabs(omega)/(2.0*Pi));
        return omega + 2.0*n*Pi;
    } else {
        return omega;
    }
}
