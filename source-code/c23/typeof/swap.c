#include <stdio.h>

#define SWAP(a, b) { \
    typeof(a) temp = a; \
    a = b; \
    b = temp; \
}

int main() {
    int x = 5, y = 10;
    printf("Before swap: x = %d, y = %d\n", x, y);
    SWAP(x, y);
    printf("After swap: x = %d, y = %d\n", x, y);
    
    float a = 1.5, b = 2.5;
    printf("Before swap: a = %.2f, b = %.2f\n", a, b);
    SWAP(a, b);
    printf("After swap: a = %.2f, b = %.2f\n", a, b);
    return 0;
}
