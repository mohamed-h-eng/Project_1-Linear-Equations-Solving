#include <iostream>

using namespace std;

// Function expects a pointer to an array of pointers (a dynamic 2D array)
int calculateSarrusDeterminant(int** matrix_ext) {
    int sum = 0;
    int subtract = 0;
    int multiply = 1;

    // --- Get positive multiplications ---
    for(int i = 0; i < 3; i++) {
        multiply = 1; 
        for(int k = 0; k < 3; k++) {
            cout << matrix_ext[k][k + i] << " ";
            multiply *= matrix_ext[k][k + i];
        }
        sum += multiply;
        
        cout << endl << endl;
    }
    cout << endl;

    // --- Get negative multiplications ---
    for(int i = 4; i > 1; i--) {
        multiply = 1; 
        for(int k = 0; k < 3; k++) {
            multiply *= matrix_ext[k][i - k];
        }
        subtract -= multiply; 
    }

    return sum + subtract;
}

int main() {
    int rows = 3;
    int cols = 5; // Extended matrix has 5 columns

    // 1. Allocate the dynamic 2D array
    int** matrix_ext = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix_ext[i] = new int[cols];
    }

    // 2. Populate the matrix (using a standard 3x5 layout for Sarrus rule)
    int initial_values[3][5] = {
        {1, 2, 3, 1, 2},
        {4, 5, 6, 4, 5},
        {7, 8, 9, 7, 8}
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix_ext[i][j] = initial_values[i][j];
        }
    }

    // 3. Call your function
    int result = calculateSarrusDeterminant(matrix_ext);
    
    cout << "Final Determinant: " << result << endl;

    // 4. CLEANUP: You MUST delete dynamically allocated memory to prevent leaks
    for (int i = 0; i < rows; i++) {
        delete[] matrix_ext[i]; // Delete each row array
    }
    delete[] matrix_ext;        // Delete the array of pointers

    return 0;
}