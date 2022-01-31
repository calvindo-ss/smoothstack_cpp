#include <iostream>
#include <iomanip>
#include <cassert>

#define MAX_ROWS 16
#define MAX_COLS 16
#define MAX_DIM MAX_ROWS * MAX_COLS

template <typename T>
void generate_matrix(T** matrix, const int x, const int y){
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            // matrix valuse range from 1-10
            matrix[i][j] = rand() % 10;
        }
    }
}

template <typename T>
void print_matrix(const T& matrix, const int x, const int y){
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            std::cout << std::setw(2) << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void print_flat_matrix(const T& matrix, const int x, const int y){
    for (int i = 0; i < x; i++){
        std::cout << std::setw(2) << matrix[i] << "  ";
    }
    std::cout << std::endl;
}

template <typename T>
void multiply_matrix(T** matrixA, T** matrixB, T** matrixC, const int A_row, const int A_col, const int B_row, const int B_col){

    T flatA[MAX_DIM];
    T flatB[MAX_DIM];
    
    // Here we flatten matrixA
    #pragma omp parallel for
    for(int i = 0; i < A_row; i++){
        for(int j = 0; j < A_col; j++){
            flatA[i * A_col + j] = matrixA[i][j];
        }
    }

    // Here we flatten matrixB
    #pragma omp parallel for
    for(int i = 0; i < B_row; i++){
        for(int j = 0; j < B_col; j++){
            flatB[j * B_row + i] = matrixB[i][j];
        }
    }

    #pragma omp parallel shared(matrixC) private(i, j, k, iOff, jOff, tot) num_threads(40)
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < A_row; i++) {
            int iOff = i * A_col; // flattened offset
            for (int j = 0; j < B_col; j++) {
                int jOff = j * B_row;   // flattened offset
                T tot = 0;
                for (int k = 0; k < B_row; k++) {
                    tot += flatA[iOff + k] * flatB[jOff + k];
                }
                matrixC[i][j] = tot;
            }
        }
    }
}

int main(void){
    int A_row = 2;    
    int A_col = 3;
    int B_row = 3;
    int B_col = 2;

    int** matrixA = new int *[A_row];
	int** matrixB = new int *[B_row];
	int** matrixC = new int *[A_row];   // matrixC has same number of rows as matrixA
	
	for (int i = 0; i < A_row; i++){
		matrixA[i] = new int[A_col];
		matrixC[i] = new int[B_col];    // matrixC has same number of columns as matrixA
	}
    for(int i = 0; i < B_row; i++){
		matrixB[i] = new int[B_col];
    }

    // assign values to matrixA
    for(int i = 0; i < A_row; i++){
        for(int j = 0; j < A_col; j++){
            matrixA[i][j] = j + 1;
        }
    }

    // assign values to matrixB
    for(int i = 0; i < B_row; i++){
        for(int j = 0; j < B_col; j++){
            matrixB[i][j] = j + 4;
        }
    }

    multiply_matrix(matrixA, matrixB, matrixC, A_row, A_col, B_row, B_col);

    assert(matrixC[0][0] == 24);
    assert(matrixC[1][1] == 30);
    
    print_matrix(matrixA, A_row, A_col);
    std::cout << "-----------" << std::endl;
    print_matrix(matrixB, B_row, B_col);
    std::cout << "-----------" << std::endl;
    print_matrix(matrixC, A_row, B_col);
    std::cout << "-----------" << std::endl;
}