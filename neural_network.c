#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_NODES 3
#define HIDDEN_NODES 5
#define OUTPUT_NODES 1

float sigmoid(float x) {
    return 1 / (1 + exp(-x));
}

void forwardPass(float input[], float weights1[][HIDDEN_NODES], float weights2[][OUTPUT_NODES], float hidden[], float output[]) {
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hidden[i] = 0;
        for (int j = 0; j < INPUT_NODES; j++) {
            hidden[i] += input[j] * weights1[j][i];
        }
        hidden[i] = sigmoid(hidden[i]);
    }

    for (int i = 0; i < OUTPUT_NODES; i++) {
        output[i] = 0;
        for (int j = 0; j < HIDDEN_NODES; j++) {
            output[i] += hidden[j] * weights2[j][i];
        }
        output[i] = sigmoid(output[i]);
    }
}

int main() {
    float input[INPUT_NODES] = {1.0, 0.5, -1.5};
    float hidden[HIDDEN_NODES];
    float output[OUTPUT_NODES];
    float weights1[INPUT_NODES][HIDDEN_NODES];
    float weights2[HIDDEN_NODES][OUTPUT_NODES];

    // Initialize weights
    // ...

    forwardPass(input, weights1, weights2, hidden, output);

    // Display output
    // ...

    return 0;
}
