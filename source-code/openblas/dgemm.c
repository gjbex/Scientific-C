#include <cblas.h>
#include <stdio.h>

int main(void) {
    // Compute: C = alpha * A * B + beta * C
    // (MxK) * (KxN) = (MxN)
    constexpr int M = 2;
    constexpr int K = 3;
    constexpr int N = 2;   
    const double alpha = 1.0;
    const double beta  = 0.0;

    // Row-major storage (natural for C)
    double A[M*K] = {
        1, 2, 3,
        4, 5, 6
    }; // A is 2x3, MxK
    double B[K*N] = {
        7,  8,
        9, 10,
        11,12
    }; // B is 3x2, KxN
    double C[M*N] = {0.0}; // C is 2x2, MxN

    // In RowMajor:
    // lda = K for A (stride between consecutive rows)
    // ldb = N for B
    // ldc = N for C
    cblas_dgemm(CblasRowMajor,
                CblasNoTrans, CblasNoTrans,
                M, N, K,
                alpha,
                A, K,
                B, N,
                beta,
                C, N);

    printf("[ %g %g ; %g %g ]\n", C[0], C[1], C[2], C[3]);
    return 0;
}

