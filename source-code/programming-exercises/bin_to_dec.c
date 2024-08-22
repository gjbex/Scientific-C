#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bin_to_dec(char str[]);

int main(int argc, char *argv[]) {
    if (argc != 2)
        errx(EXIT_FAILURE, "binary number expectec as argument");
    int n = bin_to_dec(argv[1]);
    printf("%d\n", n);
    return EXIT_SUCCESS;
}

int bin_to_dec(char str[]) {
    int nr_bits = strlen(str);
    int power = 1;
    int number = 0;
    for (int i = nr_bits - 1; i >= 0; i--) {
        if (str[i] == '1')
            number += power;
        else if (str[i] != '0')
            errx(EXIT_FAILURE, "'%s' is not a valid binary number", str);
        power *= 2;
    }
    return number;
}
