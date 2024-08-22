#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_integration.h>

/*
   Sage code for analytic result:
   x, a, b, c = var('x a b c')
   f(x) = a*x**2 + b*x + c, so
   f_int(a, b, c) = integrate(f, x, -1, 1)
   -> 2*a/3 + 2*c
 */

struct Params {
    double a, b, c;
};

double quadratic(double x, void *params);

int main(int argc, char *argv[]) {
    const double lower = -1.0, upper = 1.0;
    const double epsabs = 1.0e-7, epsrel = 1.0e-12;
    struct Params params;
    if (argc != 4) {
        errx(EXIT_SUCCESS, "specify a, b, c");
    }
    params.a = atof(argv[1]);
    params.b = atof(argv[2]);
    params.c = atof(argv[3]);
    gsl_function F;
    F.function = &quadratic;
    F.params = &params;
    double result, abserr;
    size_t nr_evals;
    gsl_integration_qng(&F, lower, upper, epsabs, epsrel, &result,
                        &abserr, &nr_evals);
    printf("%.15lf +/- %le (%d)\n", result, abserr, nr_evals);
    return EXIT_SUCCESS;
}

double quadratic(double x, void *params) {
    struct Params *p = (struct Params *) params;
    return p->a*x*x + p->b*x + p->c;
}
