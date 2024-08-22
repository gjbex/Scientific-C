#include <complex.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

double *coordinates(double min_coord, double max_coord, int steps);
double complex *z_values(double *x_coords, double *y_coords, int steps);
int *iterate_zs(double complex *zs, double complex c, int steps,
                int max_iters);
void print_results(int *ns, int steps);
void print_results_coords(int *ns, double *x_coords, double *y_coords,
                          int steps);

int main(int argc, char *argv[]) {
    const double complex c = -0.62772 - 0.42193*I;
    double x1 = -1.8, x2 = 1.8, y1 = -1.8, y2 = 1.8;
    int steps = 100;
    if (argc > 1)
        steps = atoi(argv[1]);
    double *x_coords = coordinates(x1, x2, steps);
    double *y_coords = coordinates(y1, y2, steps);
    double complex *z = z_values(x_coords, y_coords, steps);
    int *n = iterate_zs(z, c, steps, 256);
    print_results(n, steps);
    free(x_coords);
    free(y_coords);
    free(z);
    free(n);
    return EXIT_SUCCESS;
}

double *coordinates(double min_coord, double max_coord, int steps) {
    double *coords = (double *) malloc(steps*sizeof(double));
    if (coords == NULL)
        errx(EXIT_FAILURE, "can not allocate coordinates");
    double step = (max_coord - min_coord)/steps;
    double value = min_coord;
    for (int i = 0; i < steps; i++) {
        coords[i] = value;
        value += step;
    }
    return coords;
}

double complex *z_values(double *x_coords, double *y_coords, int steps) {
    size_t nr_zs = steps*steps*sizeof(double complex);
    double complex *zs = (double complex *) malloc(nr_zs);
    if (zs == NULL)
        errx(EXIT_FAILURE, "can not allocate z");
    for (int i = steps - 1; i >= 0; i--)
        for (int j = 0; j < steps; j++)
            zs[i*steps + j] = x_coords[j] + y_coords[i]*I;
    return zs;
}

int iterate_z(double complex z, double complex c, int max_iters) {
    int n = 0;
    while (cabs(z) < 2.0 && n < max_iters) {
        z = z*z + c;
        n++;
    }
    return n;
}

int *iterate_zs(double complex *zs, double complex c, int steps,
                int max_iters) {
    int *ns = (int *) malloc(steps*steps*sizeof(int));
    if (ns == NULL)
        errx(EXIT_FAILURE, "can not allocate n");
    for (int i = 0; i < steps*steps; i++)
        ns[i] = iterate_z(zs[i], c, max_iters);
    return ns;
}

void print_results(int *ns, int steps) {
    for (int i = steps - 1; i >= 0; i--)
        for (int j = 0; j < steps; j++)
            printf("%d%s", ns[i*steps + j], j < steps - 1 ? " " : "\n");
}

void print_results_coords(int *ns, double *x_coords, double *y_coords,
                          int steps) {
    for (int i = steps - 1; i >= 0; i--)
        for (int j = 0; j < steps; j++)
            printf("%le %le %d\n", x_coords[j], y_coords[i],
                   ns[i*steps + j]);
}
