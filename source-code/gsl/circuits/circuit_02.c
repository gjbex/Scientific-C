#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>

double current_i5(double R4, void *params);

int main(int argc, char *argv[]) {
    int status;
    int iter = 0, max_iters = 100;
    double R4, i5, R4_min = 20.0, R4_max = 100.0;
    gsl_root_fsolver *solver;
    gsl_function curr_func;
    curr_func.function = &current_i5;
    curr_func.params = NULL;
    solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
    gsl_root_fsolver_set(solver, &curr_func, R4_min, R4_max);
    for (iter = 1; iter <= max_iters; iter++) {
        double R4_lower, R4_upper;
        gsl_root_fsolver_iterate(solver);
        R4 = gsl_root_fsolver_root(solver);
        R4_lower = gsl_root_fsolver_x_lower(solver);
        R4_upper = gsl_root_fsolver_x_upper(solver);
        status = gsl_root_test_interval(R4_lower, R4_upper, 1e-8, 0.0);
            printf("%d: R4 = %.6lf, i5 = %.6lf\n", iter, R4,
               current_i5(R4, NULL));
        if (status != GSL_CONTINUE)
            break;
    }
    if (status == GSL_SUCCESS) {
        printf("R4 = %.6lf, i5 = %.6lf\n", R4, current_i5(R4, NULL));
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "no convergence\n");
        return EXIT_FAILURE;
    }
}

double current_i5(double R4, void *params) {
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
    int status;
    gsl_matrix_view a_matrix;
    gsl_vector_view b_vector;
    gsl_vector *x;
    gsl_permutation *perm;
    a_matrix = gsl_matrix_view_array(a_data, nr_unknowns, nr_unknowns);
    b_vector = gsl_vector_view_array(b_data, nr_unknowns);
    x = gsl_vector_alloc(nr_unknowns);
    perm = gsl_permutation_alloc(nr_unknowns);
    gsl_linalg_LU_decomp(&a_matrix.matrix, perm, &status);
    gsl_linalg_LU_solve(&a_matrix.matrix, perm, &b_vector.vector, x);
    i5 = gsl_vector_get(x, 5);
    gsl_permutation_free(perm);
    gsl_vector_free(x);
    return i5;
}
