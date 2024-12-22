#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INPUT_NODES 64
#define HIDDEN_NODES 128
#define OUTPUT_NODES 10
#define LEARNING_RATE 0.01

typedef struct {
    float weights_input_hidden[INPUT_NODES][HIDDEN_NODES];
    float weights_hidden_output[HIDDEN_NODES][OUTPUT_NODES];
    float hidden_bias[HIDDEN_NODES];
    float output_bias[OUTPUT_NODES];
} NeuralNetwork;

float sigmoid(float x) {
    return 1 / (1 + exp(-x));
}

float sigmoid_derivative(float x) {
    return x * (1 - x);
}

void initialize_weights(NeuralNetwork *nn) {
    srand(time(NULL));
    for (int i = 0; i < INPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) {
            nn->weights_input_hidden[i][j] = ((float)rand() / RAND_MAX) - 0.5;
        }
    }
    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < OUTPUT_NODES; j++) {
            nn->weights_hidden_output[i][j] = ((float)rand() / RAND_MAX) - 0.5;
        }
        nn->hidden_bias[i] = ((float)rand() / RAND_MAX) - 0.5;
    }
    for (int i = 0; i < OUTPUT_NODES; i++) {
        nn->output_bias[i] = ((float)rand() / RAND_MAX) - 0.5;
    }
}

void forward_propagation(NeuralNetwork *nn, float input[], float hidden[], float output[]) {
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hidden[i] = 0;
        for (int j = 0; j < INPUT_NODES; j++) {
            hidden[i] += input[j] * nn->weights_input_hidden[j][i];
        }
        hidden[i] += nn->hidden_bias[i];
        hidden[i] = sigmoid(hidden[i]);
    }

    for (int i = 0; i < OUTPUT_NODES; i++) {
        output[i] = 0;
        for (int j = 0; j < HIDDEN_NODES; j++) {
            output[i] += hidden[j] * nn->weights_hidden_output[j][i];
        }
        output[i] += nn->output_bias[i];
        output[i] = sigmoid(output[i]);
    }
}

void back_propagation(NeuralNetwork *nn, float input[], float hidden[], float output[], float target[]) {
    float output_error[OUTPUT_NODES];
    float hidden_error[HIDDEN_NODES];

    for (int i = 0; i < OUTPUT_NODES; i++) {
        output_error[i] = (target[i] - output[i]) * sigmoid_derivative(output[i]);
    }

    for (int i = 0; i < HIDDEN_NODES; i++) {
        hidden_error[i] = 0;
        for (int j = 0; j < OUTPUT_NODES; j++) {
            hidden_error[i] += output_error[j] * nn->weights_hidden_output[i][j];
        }
        hidden_error[i] *= sigmoid_derivative(hidden[i]);
    }

    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < OUTPUT_NODES; j++) {
            nn->weights_hidden_output[i][j] += LEARNING_RATE * output_error[j] * hidden[i];
        }
    }
    for (int i = 0; i < OUTPUT_NODES; i++) {
        nn->output_bias[i] += LEARNING_RATE * output_error[i];
    }

    for (int i = 0; i < INPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) {
            nn->weights_input_hidden[i][j] += LEARNING_RATE * hidden_error[j] * input[i];
        }
    }
    for (int i = 0; i < HIDDEN_NODES; i++) {
        nn->hidden_bias[i] += LEARNING_RATE * hidden_error[i];
    }
}

void train(NeuralNetwork *nn, float inputs[][INPUT_NODES], float targets[][OUTPUT_NODES], int epochs, int num_samples) {
    float hidden[HIDDEN_NODES];
    float output[OUTPUT_NODES];
    for (int epoch = 0; epoch < epochs; epoch++) {
        for (int i = 0; i < num_samples; i++) {
            forward_propagation(nn, inputs[i], hidden, output);
            back_propagation(nn, inputs[i], hidden, output, targets[i]);
        }
    }
}

void predict(NeuralNetwork *nn, float input[]) {
    float hidden[HIDDEN_NODES];
    float output[OUTPUT_NODES];
    forward_propagation(nn, input, hidden, output);
    printf("Predicted output:\n");
    for (int i = 0; i < OUTPUT_NODES; i++) {
        printf("%f ", output[i]);
    }
    printf("\n");
}

int main() {
    NeuralNetwork nn;
    initialize_weights(&nn);

    // Example dataset for training (inputs and targets)
    float inputs[4][INPUT_NODES] = { /*...initialize with your data...*/ };
    float targets[4][OUTPUT_NODES] = { /*...initialize with your data...*/ };
    int num_samples = 4;
    int epochs = 10000;

    // Train the neural network
    train(&nn, inputs, targets, epochs, num_samples);

    // Predict with a new input
    float new_input[INPUT_NODES] = { /*...initialize with your data...*/ };
    predict(&nn, new_input);

}
// Function to save the neural network's weights and biases to a file
void save_model(NeuralNetwork *nn, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for saving");
        return;
    }
    fwrite(nn->weights_input_hidden, sizeof(nn->weights_input_hidden), 1, file);
    fwrite(nn->weights_hidden_output, sizeof(nn->weights_hidden_output), 1, file);
    fwrite(nn->hidden_bias, sizeof(nn->hidden_bias), 1, file);
    fwrite(nn->output_bias, sizeof(nn->output_bias), 1, file);
    fclose(file);
}

// Function to load the neural network's weights and biases from a file
void load_model(NeuralNetwork *nn, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for loading");
        return;
    }
    fread(nn->weights_input_hidden, sizeof(nn->weights_input_hidden), 1, file);
    fread(nn->weights_hidden_output, sizeof(nn->weights_hidden_output), 1, file);
    fread(nn->hidden_bias, sizeof(nn->hidden_bias), 1, file);
    fread(nn->output_bias, sizeof(nn->output_bias), 1, file);
    fclose(file);
}

// Function to evaluate the neural network's performance on a test set
float evaluate(NeuralNetwork *nn, float inputs[][INPUT_NODES], float targets[][OUTPUT_NODES], int num_samples) {
    float hidden[HIDDEN_NODES];
    float output[OUTPUT_NODES];
    int correct_predictions = 0;

    for (int i = 0; i < num_samples; i++) {
        forward_propagation(nn, inputs[i], hidden, output);

        int predicted_label = 0;
        for (int j = 1; j < OUTPUT_NODES; j++) {
            if (output[j] > output[predicted_label]) {
                predicted_label = j;
            }
        }

        int actual_label = 0;
        for (int j = 1; j < OUTPUT_NODES; j++) {
            if (targets[i][j] > targets[i][actual_label]) {
                actual_label = j;
            }
        }

        if (predicted_label == actual_label) {
            correct_predictions++;
        }
    }

    return (float)correct_predictions / num_samples * 100;
}

int main() {
    NeuralNetwork nn;
    initialize_weights(&nn);

    // Example dataset for training (inputs and targets)
    float inputs[4][INPUT_NODES] = { /*...initialize with your data...*/ };
    float targets[4][OUTPUT_NODES] = { /*...initialize with your data...*/ };
    int num_samples = 4;
    int epochs = 10000;

    // Train the neural network
    train(&nn, inputs, targets, epochs, num_samples);

    // Save the trained model
    save_model(&nn, "neural_network_model.dat");

    // Load the model for evaluation
    load_model(&nn, "neural_network_model.dat");

    // Evaluate the neural network on a test set
    float test_inputs[4][INPUT_NODES] = { /*...initialize with your data...*/ };
    float test_targets[4][OUTPUT_NODES] = { /*...initialize with your data...*/ };
    int test_samples = 4;

    float accuracy = evaluate(&nn, test_inputs, test_targets, test_samples);
    printf("Model accuracy: %.2f%%\n", accuracy);

    // Predict with a new input
    float new_input[INPUT_NODES] = { /*...initialize with your data...*/ };
    predict(&nn, new_input);

    return 0;
}


