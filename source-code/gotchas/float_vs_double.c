#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    const int n = argc > 1 ? atoi(argv[1]) : 10000000;
    double *x = (double *)malloc(n * sizeof(double));
    if (x == nullptr) {
        fprintf(stderr, "Memory allocation failed for x[%d]\n", n);
        return 1;
    }
    float *y = (float *)malloc(n * sizeof(float));
    if (y == nullptr) {
        fprintf(stderr, "Memory allocation failed for y[%d]\n", n);
        free(x);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        x[i] = 1.0 + ((double) i)/n;
        y[i] = 1.0f + ((float) i)/n;
    }

    struct timespec start, end;

    // Measure time for double
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++) {
        x[i] = sin(x[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken_double = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

    // Measure time for float
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++) {
        y[i] = sinf(y[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken_float_sinf = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

    // Measure time for float
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++) {
        y[i] = sin(y[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken_float_sin = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

#include <tgmath.h>
    // Measure time for float
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++) {
        y[i] = sin(y[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken_float_tgsin = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

    printf("Time taken for sin(double):          %lf ms\n", time_taken_double);
    printf("Time taken for sinf(float):          %lf ms\n", time_taken_float_sinf);
    printf("Time taken for sin(float):           %lf ms\n", time_taken_float_sin);
    printf("Time taken for sin(float) tgmatth.:  %lf ms\n", time_taken_float_tgsin);

    free(x);
    free(y);
    return 0;
}
