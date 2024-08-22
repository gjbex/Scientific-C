#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void read_vector(double v[], int n);
double norm(double v[], int n);

int main(int argc, char *argv[]) {
    const int max_nr_comps = 5;
    double v[max_nr_comps];
    int n;
    if (argc == 1) {
        errx(EXIT_FAILURE, "expecting number of components");
    }
    n = atoi(argv[1]);
    read_vector(v, n);
    printf("norm = %lf\n", norm(v, n));
    return EXIT_SUCCESS;
}

void read_vector(double v[], int n) {
    for (int i = 0; i < n; i++) {
        scanf("%lf", &(v[i]));
    }
}

double norm(double v[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += v[i]*v[i];
    }
    return sqrt(sum);
}
