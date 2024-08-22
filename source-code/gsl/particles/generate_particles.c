#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int main(int argc, char *argv[]) {
    const double r_mean = 1.4e-9;
    const double v_p_mean = 4.0e4;
    const double v_e_mean = 5.0e5;
    const double degree_of_freedom = 2.0;
    int nr_particles = 10, i;
    gsl_rng *rng;
    gsl_rng_env_setup();
    rng = gsl_rng_alloc(gsl_rng_default);
    if (argc > 1)
        nr_particles = atoi(argv[1]);
    for (i = 0; i < nr_particles; i++) {
        double x, y, v_x, v_y, r, v;
        int q = gsl_rng_uniform(rng) < 0.5 ? -1 : 1;
        r = sqrt(gsl_ran_chisq(rng, degree_of_freedom))*r_mean;
        gsl_ran_dir_2d(rng, &x, &y);
        x *= r;
        y *= r;
        if (q > 0) {
            v = sqrt(gsl_ran_chisq(rng, degree_of_freedom))*v_p_mean;
        } else {
            v = sqrt(gsl_ran_chisq(rng, degree_of_freedom))*v_e_mean;
        }
        gsl_ran_dir_2d(rng, &v_x, &v_y);
        v_x *= v;
        v_y *= v;
        printf("%.12le %.12le %.12le %.12le %d\n", x, y, v_x, v_y, q);
    }
    gsl_rng_free(rng);
    return EXIT_SUCCESS;
}
