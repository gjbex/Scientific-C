#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void read_vector(double v[], int n);
double dot(double v1[], double v2[], int n);

int main(int argc, char *argv[]) {
    const int max_nr_comps = 5;
    double x1[max_nr_comps], x2[max_nr_comps];
    int n;
    if (argc == 1) {
        errx(EXIT_FAILURE, "expecting number of components");
    }
    n = atoi(argv[1]);
    read_vector(x1, n);
    read_vector(x2, n);
    printf("dot product = %lf\n", dot(x1, x2, n));
    return EXIT_SUCCESS;
}

void read_vector(double v[], int n) {
    for (int i = 0; i < n; i++) {
        scanf("%lf", &(v[i]));
    }
}

double dot(double v1[], double v2[], int n) {
    double product = 0.0;
    for (int i = 0; i < n; i++) {
        product += v1[i]*v2[i];
    }
    return product;
}
