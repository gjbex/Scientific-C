#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    complex double z1 = 1.0 + 0.5*I, z2 = 3.0 - 2.0*I;
    complex double z3 = z1 + z2;
    printf("%lf %c %lfi\n",
            creal(z3), cimag(z3) >= 0.0 ? '+' : '-', fabs(cimag(z3)));
    return EXIT_SUCCESS;
}
