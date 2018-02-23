#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <sstream>
using namespace std;

default_random_engine generator;
uniform_real_distribution<double> randVal(1, 10);

double getVal(double *array_1, double *array_2, int n, int i, int j){
    double val = 0;
    for (int k = 0; k < n; k++)
    {
        val += array_1[i * n + k] * array_2[j * n + k];
    }
    return val;
}

void transpose(double **array, double **new_array, int rows, int cols){
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            new_array[j][i] = array[i][j];
        }
    }
}

void flatten(double **input_array, double *output_array, int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            output_array[i * n + j] = input_array[i][j];
        }
    }
}

int main(int argc, char *argv[]){
    int n;
    istringstream iss(argv[1]);
    iss >> n;
    // cout << "Matrix size " << n << " x " << n << "" ".\n";

    // First matrix
    double **matrix_1;
    matrix_1 = new double *[n];

    for (int i = 0; i < n; i++){
        matrix_1[i] = new double[n];
    }

    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++)
        {
            matrix_1[row][col] = randVal(generator);
        }
    }

    // Second matrix
    double **matrix_2;
    matrix_2 = new double *[n];

    for (int i = 0; i < n; i++){
        matrix_2[i] = new double[n];
    }

    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++)
        {
            matrix_2[row][col] = randVal(generator);
        }
    }

    // Matrix to store result
    double **result;
    result = new double *[n];

    for (int i = 0; i < n; i++){
        result[i] = new double[n];
    }

    // transpose second matrix to exploit spatial locality.
    double **new_matrix_2;
    new_matrix_2 = new double *[n];

    for (int i = 0; i < n; i++){
        new_matrix_2[i] = new double[n];
    }
    transpose(matrix_2, new_matrix_2, n, n);

    double *flattened_matrix_1 = new double[n * n];
    double *flattened__transposed_matrix_2 = new double[n * n];

    // flatten matrices
    flatten(matrix_1, flattened_matrix_1, n);
    flatten(new_matrix_2, flattened__transposed_matrix_2, n);

    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < n; i++){
        #pragma omp parallel for
        for (int j = 0; j < n; j++){
            result[i][j] = getVal(flattened_matrix_1, flattened__transposed_matrix_2, n, i / n, j % n);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    // cout << "Elapsed time: " << elapsed.count() << ".\n";
    cout << elapsed.count() << endl;

    // IMPORTANT- Release memory. Otherwise made in stack -> seg faults
    delete matrix_1;
    delete matrix_2;
    delete new_matrix_2;
    delete flattened_matrix_1;
    delete flattened__transposed_matrix_2;
    delete result;
}
