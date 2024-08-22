#include <stdbool.h>
#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_fft_real.h>

double *read_data(FILE *fp, int *n);
double *mirror(double *data, int n);

int main(int argc, char *argv[]) {
    const int stride = 1;
    double t = 1.0;
    if (argc < 2)
        errx(EXIT_FAILURE, "no data file specified");
    if (argc > 2)
        t = atof(argv[2]);
    FILE *fp;
    if ((fp = fopen(argv[1], "r")) == NULL)
        errx(EXIT_FAILURE, "can not open file '%s'", argv[1]);
    int n = 0;
    double *data = read_data(fp, &n);
    fclose(fp);
    gsl_fft_real_wavetable *wavetable = gsl_fft_real_wavetable_alloc(n);
    gsl_fft_real_workspace *workspace = gsl_fft_real_workspace_alloc(n);
    gsl_fft_real_transform(data, stride, n, wavetable, workspace);
    for (int i = 0; i < n/2; i += 2)
        printf("%f %f\n", i/(2*t),
               (data[i]*data[i] + data[i+1]*data[i+1])/n);
    gsl_fft_real_workspace_free(workspace);
    gsl_fft_real_wavetable_free(wavetable);
    free(data);
    return EXIT_SUCCESS;
}

bool is_comment(char str[]) {
    int i = 0;
    while (i < strlen(str) && isspace(str[i]))
        i++;
    return str[i] == '#';
}

bool is_header(char str[]) {
    int i = 0;
    while (i < strlen(str) && isspace(str[i]))
        i++;
    return isalpha(str[i]);
}

void skip_header(FILE **fp) {
    char buffer[1014];
    fpos_t pos;
    while (!feof(*fp)) {
        fgetpos(*fp, &pos);
        char *p = fgets(buffer, 1023, *fp);
        if (p == NULL)
            errx(EXIT_FAILURE, "error reading input file");
        if (is_comment(buffer) || is_header(buffer))
            continue;
        else
            break;
    }
    fsetpos(*fp, &pos);
}

double *read_data(FILE *fp, int *n) {
    const int delta_size = 1000;
    double *data, t, theta;
    if (*n <= 0)
        *n = delta_size;
    if ((data = (double *) malloc(*n*sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "can not allocate data with %d doubles", *n);
    skip_header(&fp);
    int i = 0;
    while (fscanf(fp, "%lf %lf", &t, &theta) == 2) {
        data[i++] = theta;
        if (i == *n) {
            *n += delta_size;
            double *tmp = (double *) realloc(data, *n*sizeof(double));
            if (tmp == NULL)
                errx(EXIT_FAILURE, "can not allocate data with %d doubles",
                     *n);
            data = tmp;
        }
    }
    *n = i;
    return data;
}

double *mirror(double *data, int n) {
    double *mirrored;
    if ((mirrored = (double *) malloc(2*n*sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "can not allocate data with %d doubles", 2*n);
    for (int i = 0; i < n; i++) {
        mirrored[i] = data[i];
        mirrored[n - i - 1] = data[i];
    }
    return mirrored;
}
