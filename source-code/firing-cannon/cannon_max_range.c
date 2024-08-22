#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_odeiv2.h>

#define X   y[0]
#define V_X y[1]
#define Y   y[2]
#define V_Y y[3]

const double g = 9.81;        /* m/s^2 */
const double v_0 = 700.0;     /* m/s */
const double B2_m = 4.0e-5;   /* 1/m */
const double y_d = 1.0e4;     /* m */
const double PI = 3.14159265359;

int func(double t, const double y[], double f[], void *params);
double shot_range(double alpha, void *params);
double deg2rad(double angle);
double rad2deg(double angle);

int main(int argc, char *argv[]) {
    int status;
    int iter_nr = 0, nr_iters = 100;
    gsl_function F;
    gsl_min_fminimizer *minimizer;
    double min_alpha = deg2rad(3.0), max_alpha = deg2rad(87.0),
           alpha = deg2rad(30.0), extrema[2];
    if (argc > 1)
        alpha = deg2rad(atof(argv[1]));
    F.function = &shot_range;
    F.params = extrema;
    minimizer = gsl_min_fminimizer_alloc(gsl_min_fminimizer_brent);
    gsl_min_fminimizer_set(minimizer, &F, alpha, min_alpha, max_alpha);
    fprintf(stderr, "# iter_nr min_alpha max_alpha alpha\n");
    fprintf(stderr, "%d %.3f %.3f %.3f %.1f\n",
            iter_nr, rad2deg(min_alpha), rad2deg(max_alpha),
            rad2deg(alpha), -shot_range(alpha, &extrema));
    do {
        iter_nr++;
        status = gsl_min_fminimizer_iterate(minimizer);
        alpha = gsl_min_fminimizer_x_minimum(minimizer);
        min_alpha = gsl_min_fminimizer_x_lower(minimizer);
        max_alpha = gsl_min_fminimizer_x_upper(minimizer);
        status = gsl_min_test_interval(min_alpha, max_alpha, 1e-6, 0.0);
        fprintf(stderr, "%d %.3f %.3f %.3f %.1f\n",
                iter_nr, rad2deg(min_alpha), rad2deg(max_alpha),
                rad2deg(alpha), extrema[0]);
    } while (status == GSL_CONTINUE && iter_nr < nr_iters);
    if (status == GSL_SUCCESS) {
        printf("converged at %.3f, range %.1f, max. altitude %.1f\n",
               rad2deg(alpha), extrema[0], extrema[1]);
    } else {
        warnx("no convergence");
    }
    gsl_min_fminimizer_free(minimizer);
    return status;
}

int func(double t, const double y[], double f[], void *params) {
    double v = sqrt(V_X*V_X + V_Y*V_Y);
    double corr = exp(-Y/y_d);
    f[0] = V_X;
    f[1] = -B2_m*corr*v*V_X;
    f[2] = V_Y;
    f[3] = -g - B2_m*corr*v*V_Y;
    return GSL_SUCCESS;
}

double shot_range(double alpha, void *params) {
    gsl_odeiv2_system sys = {func, NULL, 4, NULL};
    gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(
            &sys, gsl_odeiv2_step_rkf45, 1.0e-6, 1.0e-6, 0.0
    );
    int i = 1;
    double t = 0.0;
    double y[4];
    double h_max = 0.0;
    X = Y = 0.0;
    V_X = v_0*cos(alpha);
    V_Y = v_0*sin(alpha);
    while (y[2] >= 0.0) {
        double t_i = i/50.0;
        int status = gsl_odeiv2_driver_apply(driver, &t, t_i, y);
        if (status != GSL_SUCCESS) {
            warnx("apply status = %d", status);
            break;
        }
        if (Y > h_max)
            h_max = Y;
        i++;
    }
    gsl_odeiv2_driver_free(driver);
    *((double *) params) = X;
    *(1 + (double *) params) = h_max;
    return -X;
}

double deg2rad(double angle) {
    return 2*PI*angle/360.0;
}

double rad2deg(double angle) {
    return 360.0*angle/(2*PI);
}
