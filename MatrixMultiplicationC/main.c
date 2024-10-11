#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX_SIZE 2048  // Tamaño máximo de la matriz
#define NUM_TESTS 5    // Número de pruebas por tamaño de matriz

double a[MAX_SIZE][MAX_SIZE];
double b[MAX_SIZE][MAX_SIZE];
double c[MAX_SIZE][MAX_SIZE];

// Función para inicializar matrices
void initialize_matrices(int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = (double) rand() / RAND_MAX;
            b[i][j] = (double) rand() / RAND_MAX;
            c[i][j] = 0;
        }
    }
}

// Función para multiplicar matrices
void multiply_matrices(int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                c[i][j] += a[i][k] * b[k][j];  // Sumar en lugar de asignar
            }
        }
    }
}

// Función para realizar las pruebas
void run_tests(int size) {
    struct timeval start, stop;
    double total_time = 0;

    for (int test = 0; test < NUM_TESTS; ++test) {
        initialize_matrices(size);

        // Medir el tiempo de ejecución
        gettimeofday(&start, NULL);
        multiply_matrices(size);
        gettimeofday(&stop, NULL);

        // Calcular el tiempo total en segundos
        double diff = stop.tv_sec - start.tv_sec
                      + 1e-6 * (stop.tv_usec - start.tv_usec);
        total_time += diff;

        printf("Test %d para tamaño %d: %0.6f segundos\n", test + 1, size, diff);
    }

    // Calcular el tiempo promedio
    double average_time = total_time / NUM_TESTS;
    printf("Promedio para tamaño %d: %0.6f segundos\n\n", size, average_time);
}

int main() {
    // Definir los tamaños de matrices a probar
    int matrix_sizes[] = {256, 512, 1024, 2048};
    int num_sizes = sizeof(matrix_sizes) / sizeof(matrix_sizes[0]);

    for (int i = 0; i < num_sizes; ++i) {
        int size = matrix_sizes[i];
        printf("=== Pruebas para tamaño de matriz: %dx%d ===\n", size, size);
        run_tests(size);
    }

    return 0;
}
