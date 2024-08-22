#include <err.h>
#include <stdio.h>
#include <stdlib.h>

void print_binary(int n);

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int n = atoi(argv[1]);
        print_binary(n);
        return EXIT_SUCCESS;
    } else {
        errx(EXIT_FAILURE, "no number specified");
    }
}

void print_binary(int n) {
    if (n > 1)
        print_binary(n/2);
    printf("%d", n % 2);
}
