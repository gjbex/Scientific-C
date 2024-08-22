#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "cl_params.h"

typedef struct {
    double n_a, n_b, n_ab, n;
} Molecules;

void setup(gsl_rng **rng);
void initialize_system(Molecules *molecules, Params *params);
void next_time(double *t, Molecules *molecules, Params *params,
               gsl_rng *rng);
void update_system(Molecules *molecules, Params *params, gsl_rng *rng);
void print_system(Molecules *molecules, double t);

int main(int argc, char *argv[]) {
    gsl_rng *rng;
    Params params;
    initCL(&params);
    parseCL(&params, &argc, &argv);
    if (params.verbose)
        dumpCL(stdout, "# ", &params);
    setup(&rng);
    Molecules molecules;
    initialize_system(&molecules, &params);
    double t = 0.0;
    while (t < params.t_max) {
        next_time(&t, &molecules, &params, rng);
        update_system(&molecules, &params, rng);
        print_system(&molecules, t);
    }
    gsl_rng_free(rng);
    finalizeCL(&params);
    return EXIT_SUCCESS;
}

void setup(gsl_rng **rng) {
    gsl_rng_env_setup();
    *rng = gsl_rng_alloc(gsl_rng_default);
    if (*rng == NULL)
        errx(EXIT_FAILURE, "can't initialize rng");
}

void initialize_system(Molecules *molecules, Params *params) {
    molecules->n_a = params->n_a;
    molecules->n_b = params->n_b;
    molecules->n_ab = params->n_ab;
}

void next_time(double *t, Molecules *molecules, Params *params,
               gsl_rng *rng) {
    double rate = params->k_D*molecules->n_a*molecules->n_b +
                  params->k_B*molecules->n_ab;
    *t += gsl_ran_exponential(rng, 1.0/rate);
}

void update_system(Molecules *molecules, Params *params, gsl_rng *rng) {
    double rate = params->k_D*molecules->n_a*molecules->n_b +
                  params->k_B*molecules->n_ab;
    double p = gsl_rng_uniform(rng);
    double p_D = params->k_D*molecules->n_a*molecules->n_b/rate;
    if (p < p_D) {
        molecules->n_a -= 1.0;
        molecules->n_b -= 1.0;
        molecules->n_ab += 1.0;
    } else {
        molecules->n_a += 1.0;
        molecules->n_b += 1.0;
        molecules->n_ab -= 1.0;
    }
}

void print_system(Molecules *molecules, double t) {
    printf("%lf %lf %lf %lf\n", t, molecules->n_a, molecules->n_b,
            molecules->n_ab);
}
