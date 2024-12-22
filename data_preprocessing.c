#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 10

void normalizeData(float data[][MAX_COLS], int rows, int cols) {
    float min, max;
    for (int i = 0; i < cols; i++) {
        min = data[0][i];
        max = data[0][i];
        for (int j = 1; j < rows; j++) {
            if (data[j][i] < min) min = data[j][i];
            if (data[j][i] > max) max = data[j][i];
        }
        for (int j = 0; j < rows; j++) {
            data[j][i] = (data[j][i] - min) / (max - min);
        }
    }
}

int main() {
    float data[MAX_ROWS][MAX_COLS];
    int rows, cols;

    // Initialize data
    // ...

    normalizeData(data, rows, cols);

    // Display normalized data
    // ...

    return 0;
}
