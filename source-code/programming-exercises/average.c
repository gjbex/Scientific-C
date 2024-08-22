#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n = 0;
    double sum = 0.0, x;
    for (;;) {
        scanf("%lf", &x);
        if (x >= 0) {
            sum += x;
            n++;
        } else {
            break;
        }
    }
    if (n > 0) {
        printf("average = %lf\n", sum/n);
        return EXIT_SUCCESS;
    } else {
        printf("no input given\n");
        return EXIT_FAILURE;
    }
}
