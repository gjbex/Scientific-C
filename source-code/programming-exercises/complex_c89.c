#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Complex {
    double re, im;
};

struct Complex complex_sum(struct Complex z1, struct Complex z2);

int main(void) {
    struct Complex z1 = {1.0, 0.5}, z2 = {3.0, -2.0};
    struct Complex z3 = complex_sum(z1, z2);
    printf("%lf %c %lfi\n", z3.re, z3.im >= 0.0 ? '+' : '-', fabs(z3.im));
    return EXIT_SUCCESS;
}

struct Complex complex_sum(struct Complex z1, struct Complex z2) {
    struct Complex z3 = {z1.re + z2.re, z1.im + z2.im};
    return z3;
}
