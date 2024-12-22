#include <stdio.h>

#define MAX_DATA_POINTS 100

void linearRegression(float x[], float y[], int n, float *m, float *c) {
    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    *m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    *c = (sumY - (*m) * sumX) / n;
}

int main() {
    float x[MAX_DATA_POINTS], y[MAX_DATA_POINTS];
    float m, c;
    int n;

    // Initialize data points
    // ...

    linearRegression(x, y, n, &m, &c);

    // Display results
    // ...

    return 0;
}
