#include <limits.h>
#include <stdckdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int a = INT_MAX;
    int b = 1;
    int result;

    printf("Unchecked addition: %d + %d = %d\n", a, b, a + b);

    if (!ckd_add(&result, a, b)) {
        printf("Addition result: %d\n", result);
    } else {
        printf("Overflow occurred during addition.\n");
    }

    const int n = argc > 1 ? atoi(argv[1]) : 10'000'000;
    int *x = (int *)malloc(n * sizeof(int));
    if (x == nullptr) {
        fprintf(stderr, "Memory allocation failed for x[%d]\n", n);
        return 1;
    }
    struct timespec start, end;
    for (int i = 0; i < n; i++) {
        x[i] = i;
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++) {
        x[i] += 15;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_not_checked = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

    for (int i = 0; i < n; i++) {
        x[i] = i;
    }
    int failures = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < n; i++) {
        if (ckd_add(&x[i], x[i], 15)) {
            failures++;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_checked = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

    printf("Time taken without overflow check: %lf ms\n", time_not_checked);
    printf("Time taken with overflow check:    %lf ms, failuers %d\n", time_checked, failures);

    free(x);
    return 0;
}
