#include <stdio.h>

int main() {
    unsigned _BitInt(4) a = 1u;
    unsigned _BitInt(6) b = 0b10'0000u;

    printf("a = %04b, b = %b\n", a, b);
    printf("a + b = %b\n", a + b);
    return 0;
}
