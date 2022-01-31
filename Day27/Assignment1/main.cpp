#include <iostream>
#include <iomanip>
#include <cassert>

#define MAX_ROWS 16
#define MAX_COLS 16
#define MAX_DIM MAX_ROWS * MAX_COLS

template <typename T>
void generate_matrix(T** matrix, const int dimension){
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++){
            // matrix valuse range from 1-10
            matrix[i][j] = rand() % 10;
        }
    }
}

template <typename T>
void print_matrix(const T& matrix, const int dimension){
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++){
            std::cout << std::setw(2) << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void print_flat_matrix(const T& matrix, const int dimension){
    for (int i = 0; i < dimension; i++){
        std::cout << std::setw(2) << matrix[i] << "  ";
        //if(i % y == 0){
        //    std::cout << std::endl;
        //}
    }
    std::cout << std::endl;
}

template <typename T>
void multiply_matrix(T** matrixA, T** matrixB, T** matrixC, const int dimension){

    T flatA[MAX_DIM];
    T flatB[MAX_DIM];
    
    // Here we flatten matrix
    #pragma omp parallel for
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            flatA[i * dimension + j] = matrixA[i][j];
            flatB[j * dimension + i] = matrixB[i][j];
        }
    }

    #pragma omp parallel shared(matrixC) private(i, j, k, iOff, jOff, tot) num_threads(40)
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < dimension; i++) {
            int iOff = i * dimension;
            for (int j = 0; j < dimension; j++) {
                int jOff = j * dimension;
                T tot = 0;
                for (int k = 0; k < dimension; k++) {
                    tot += flatA[iOff + k] * flatB[jOff + k];
                }
                matrixC[i][j] = tot;
            }
        }
    }
}

int main(void){
    int d = 3;

    int** matrixA = new int *[d];
	int** matrixB = new int *[d];
	int** matrixC = new int *[d];
	
	for (int i = 0; i < d; i++) {
		matrixA[i] = new int[d];
		matrixB[i] = new int[d];
		matrixC[i] = new int[d];
	}

    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            matrixA[i][j] = j+1;
            matrixB[i][j] = j + 3;
        }
    }

    multiply_matrix(matrixA, matrixB, matrixC, d);

    assert(matrixC[0][0] == 18);
    assert(matrixC[1][1] == 24);
    assert(matrixC[2][2] == 30);

    // Randomly generated matrix multiplication
    generate_matrix(matrixA, d);
    print_matrix(matrixA, d);
    std::cout << "-----------" << std::endl;
    generate_matrix(matrixB, d);
    print_matrix(matrixB, d);
    std::cout << "-----------" << std::endl;

    multiply_matrix(matrixA, matrixB, matrixC, d);

    print_matrix(matrixC, d);
    std::cout << "-----------" << std::endl;
}