#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <rows> <cols>\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // Allocate memory for a 2D array
    double *data = (double *) malloc(rows * cols * sizeof(double));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Create a view of the data as a 2D array
    double (*array)[cols] = (double (*)[cols]) data;

    // Initialize the array with some values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = (double) i*cols + j;
        }
    }

    // Print the array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%6.1lf ", array[i][j]);
        }
        printf("\n");
    }

    // Free the allocated memory
    free(data);

    return 0;
}
