#include <stdio.h>
#include <stdlib.h>

void multiplyMatrices(int firstMatrix[][10], int secondMatrix[][10], int result[][10], int rowFirst, int colFirst, int rowSecond, int colSecond) {
    for (int i = 0; i < rowFirst; i++) {
        for (int j = 0; j < colSecond; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colFirst; k++) {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

int main() {
    int rowFirst, colFirst, rowSecond, colSecond;
    int firstMatrix[10][10], secondMatrix[10][10], result[10][10];

    // Initialize matrix dimensions
    // ...

    // Multiply matrices
    multiplyMatrices(firstMatrix, secondMatrix, result, rowFirst, colFirst, rowSecond, colSecond);

    // Display the result
    // ...

    return 0;
}
