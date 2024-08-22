#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
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
double shot_range(double alpha, double *h_max);
double deg2rad(double angle);
double rad2deg(double angle);

int main(int argc, char *argv[]) {
    int iter_nr = 0, nr_iters = 500;
    double min_alpha = deg2rad(3.0), max_alpha = deg2rad(87.0),
           delta_alpha = deg2rad(0.5), h_max;
    printf("# alpha range max_height\n");
    for (double alpha = min_alpha; alpha <= max_alpha;
            alpha += delta_alpha) {
        printf("%lf %lf", rad2deg(alpha), shot_range(alpha, &h_max));
        printf(" %lf\n", h_max);
    }
    return EXIT_SUCCESS;
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

double shot_range(double alpha, double *h_max) {
    gsl_odeiv2_system sys = {func, NULL, 4, NULL};
    gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(
            &sys, gsl_odeiv2_step_rkf45, 1.0e-6, 1.0e-6, 0.0
    );
    int i = 1;
    double t = 0.0;
    double y[4];
    *h_max = 0.0;
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
        if (Y > *h_max)
            *h_max = Y;
        i++;
    }
    gsl_odeiv2_driver_free(driver);
    return X;
}

double deg2rad(double angle) {
    return 2*PI*angle/360.0;
}

double rad2deg(double angle) {
    return 360.0*angle/(2*PI);
}
