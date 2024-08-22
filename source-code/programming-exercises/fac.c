#include <stdio.h>
#include <stdlib.h>

long fac(long n);
long fac_r(long n);

int main(int argc, char *argv[]) {
    long n = 5;
    int recursive = 0;
    if (argc > 1) {
        n = atol(argv[1]);
    }
    if (argc > 2) {
        recursive = atoi(argv[2]);
    }
    if (recursive) {
        printf("fac_r(%ld) = %ld\n", n, fac_r(n));
    } else {
        printf("fac(%ld) = %ld\n", n, fac(n));
    }
    return EXIT_SUCCESS;
}

long fac(long n) {
    long prod = 1;
    for (long i = 2; i <= n; i++)
        prod *= i;
    return prod;
}

long fac_r(long n) {
    if (n == 0)
        return 1;
    else
        return n*fac_r(n-1);
}
