#include <stdio.h>
#include <stdlib.h>

void bit_convert(int n);

int main(int argc, char *argv[]) {
    int n;
    if (argc < 2) {
        printf("### error: no number to convert\n");
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    bit_convert(n);
    return EXIT_SUCCESS;
}

void bit_convert(int n) {
    const int nr_bits = 8*sizeof(int);
    int bits[nr_bits], last_bit = nr_bits;
    do {
        bits[--last_bit] = n % 2;
        n /= 2;
    } while (n > 0);
    for (int i = last_bit; i < nr_bits; i++)
        printf("%d", bits[i]);
    printf("\n");
}
