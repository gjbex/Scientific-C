#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_linalg.h>

double current_i5(double R4);

int main(int argc, char *argv[]) {
    const double R4_min = 5.0, R4_max = 100.0, R4_delta = 0.1;
    double R4, i5;
    for (R4 = R4_min; R4 <= R4_max; R4 += R4_delta) {
        i5 = current_i5(R4);
        printf("%.6lf %.6lf\n", R4, i5);
    }
    return EXIT_SUCCESS;
}

double current_i5(double R4) {
    const int nr_unknowns = 6;
    const double E = 5.0;
    const double R1 = 10.0, R2 = 20.0, R3 = 30.0, R5 = 1000.0;
    double a_data[] = {
    /*    i0,   i1,   i2,    i3,    i4,   i5   */
         1.0,  1.0, -1.0,   0.0,   0.0,  0.0,
         0.0,  0.0,  1.0,   0.0,  -1.0, -1.0,
         0.0, -1.0,  0.0,   1.0,   0.0,  1.0,
         0.0,   R1,  0.0,    R3,   0.0,  0.0,
         0.0,   R1,   R2,   0.0,   0.0,   R5,
         0.0,  0.0,  0.0,    R3,    R4,  -R5,
    };
    double b_data[] = {0.0, 0.0, 0.0, E, 0.0, 0.0};
    double i5;
    int signum, status;
    gsl_matrix_view a_matrix;
    gsl_vector_view b_vector;
    gsl_vector *x;
    gsl_permutation *perm;
    a_matrix = gsl_matrix_view_array(a_data, nr_unknowns, nr_unknowns);
    b_vector = gsl_vector_view_array(b_data, nr_unknowns);
    x = gsl_vector_alloc(nr_unknowns);
    perm = gsl_permutation_alloc(nr_unknowns);
    status = gsl_linalg_LU_decomp(&a_matrix.matrix, perm, &signum);
    if (status != GSL_SUCCESS)
        warnx("### warning: exit status of LU decomp is %d\n", status);
    status = gsl_linalg_LU_solve(&a_matrix.matrix, perm,
                                 &b_vector.vector, x);
    if (status != GSL_SUCCESS)
        warnx("### warning: exit status of LU solve is %d\n", status);
#ifdef VERBOSE
    fprintf(stderr, "%.8lf %.8le\n",
            R4, gsl_linalg_LU_det(&a_matrix.matrix, signum));
#endif
    i5 = gsl_vector_get(x, 5);
    gsl_permutation_free(perm);
    gsl_vector_free(x);
    return i5;
}
