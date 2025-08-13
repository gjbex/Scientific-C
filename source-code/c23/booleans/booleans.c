#include <stdio.h>

int main() {
    bool isTrue = true;
    bool isFalse = false;

    if (isTrue) {
        printf("isTrue is true\n");
    } else {
        printf("isTrue is false\n");
    }

    if (isTrue && isFalse) {
        printf("Both are true\n");
    } else {
        printf("At least one is false\n");
    }

    return 0;
}
