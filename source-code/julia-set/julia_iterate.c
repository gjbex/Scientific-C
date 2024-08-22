#include <err.h>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

double julia_iterate(double complex *z, const double complex c);

int main(int argc, char *argv[]) {
    const double complex c = -0.62772 - 0.42193*I;
    int n = 100;
    if (argc < 3)
        errx(EXIT_FAILURE, "complex value expected, real imag");
    double re = atof(argv[1]);
    double im = atof(argv[2]);
    if (argc > 3)
        n = atoi(argv[3]);
    double complex z = re + im*I;
    for (int i = 0; i < n; i++)
        printf("%d %le\n", i, julia_iterate(&z, c));
    return EXIT_SUCCESS;
}

double julia_iterate(double complex *z, const double complex c) {
    double norm = cabs(*z);
    *z = (*z)*(*z) + c;
    return norm;
}
