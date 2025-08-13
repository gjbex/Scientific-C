#include <stdio.h>

int main(void) {
    unsigned _BitInt(3) counter = 0u;

    printf("size = %zu\n\n", sizeof(counter));

    for (int i = 0; i < 15; i++) {
        printf("Counter: %u\n", counter);
        counter++;
    }

    return 0;
}
