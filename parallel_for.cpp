#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <sstream>
using namespace std;


default_random_engine generator;
uniform_real_distribution<double> randVal(1, 10);


double getVal(double **array_1, double **array_2, int n, int i, int j){
    double val = 0;
    for (int k = 0; k < n ; k++){
        val += array_1[i][k] * array_2[k][j];
    }
    return val;
}

int main(int argc, char *argv[]){
    // cout << "Enter matrix size (n): ";
    int n;
    istringstream iss(argv[1]);
    iss >> n;
    // cin >> n;
    cout << "Matrix size " << n << " x " << n << "" ".\n";

    // First matrix
    double **matrix_1;
    matrix_1 = new double*[n];

    for (int i  = 0 ; i < n ; i++){
        matrix_1[i] = new double[n]; 
    }

    for (int row = 0; row < n ; row++){
        for (int col = 0; col < n ; col++){
            matrix_1[row][col] = randVal(generator);
        }
    }

    // Second matrix
    double **matrix_2;
    matrix_2 = new double*[n];

    for (int i  = 0 ; i < n ; i++){
        matrix_2[i] = new double[n]; 
    }

    for (int row = 0; row < n ; row++){
        for (int col = 0; col < n ; col++){
            matrix_2[row][col] = randVal(generator);
        }
    }

    // Matrix to store result
    double **result;
    result = new double*[n];

    for (int i  = 0 ; i < n ; i++){
        result[i] = new double[n]; 
    }

    cout << "Calculating multiplication...\n";
    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < n; i++ ){
        #pragma omp parallel for
        for (int j = 0; j < n; j++){
            result[i][j] = getVal(matrix_1, matrix_2, n, i, j);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Elapsed time: " << elapsed.count() << ".\n";


    // cout << "\n\n\nResultant matrix: \n";

    // for (int row = 0; row < n ; row++){
    //     for (int col = 0; col < n ; col++){
    //         cout << result[row][col] <<  (col == n-1 ? "" : "\t");
    //     }
    //     cout << "\n";
    // }


    delete matrix_1;
    delete matrix_2;
    delete result;   


}


