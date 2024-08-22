#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/*
   Sage code for analytic result:
   x, a, b, c = var('x a b c')
   f(x) = a*x**2 + b*x + c, so
   f_int(a, b, c) = integrate(f, x, -1, 1)
   -> 2*a/3 + 2*c
 */

double quadratic(double x, double a, double b, double c);
double integrate(double lower, double upper, int n,
                double a, double b, double c);

int main(int argc, char *argv[]) {
    double a, b, c;
    int n;
    if (argc != 5) {
        errx(EXIT_SUCCESS, "specify a, b, c, and n");
    }
    a = atof(argv[1]);
    b = atof(argv[2]);
    c = atof(argv[3]);
    n = atoi(argv[4]);
    double result = integrate(-1.0, 1.0, n, a, b, c);
    printf("%lf\n", result);
    return EXIT_SUCCESS;
}

double quadratic(double x, double a, double b, double c) {
    return a*x*x + b*x + c;
}

double integrate(double lower, double upper, int n,
                double a, double b, double c) {
    double delta = (upper - lower)/n;
    double x = lower;
    double integral = 0.0;
    for (int i = 0; i < n; i++) {
        integral += delta*quadratic(x, a, b, c);
        x += delta;
    }
    return integral;
}
