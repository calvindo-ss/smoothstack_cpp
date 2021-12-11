#include <iostream>
#include <cassert>
#include <stdio.h>
#include <time.h>
#include <vector>

// returns a randomly generated matrix (x,y)
std::vector<std::vector<int>> generate_mat(int x, int y){
    std::vector<std::vector<int>> matrix(x, std::vector<int>(y));

    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            // matrix valuse range from 1-10
            matrix[i][j] = rand() % 10;
        }
    }
	return matrix;
}

void print_mat(std::vector<std::vector<int>> matrix){
    // gets size of 2d vector
    int size_x = matrix.size();
    int size_y = matrix[0].size();

    std::cout << "########################" << std::endl;

    for (int i = 0; i < size_x; i++){
        for (int j = 0; j < size_y; j++){
            std::cout << matrix[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> mult_mat(std::vector<std::vector<int>> mult1, std::vector<std::vector<int>> mult2){
    // gets sizes for matrix product
    int r1 = mult1.size();
    int r2 = mult2.size();
    int c2 = mult2[0].size();

    std::vector<std::vector<int>> result(r1, std::vector<int>(c2));

    for (int i = 0; i < r1; i++){           // loops row of mat1
        for (int j = 0; j < c2; j++){       // loops column of mat2
            for (int k = 0; k < r2; k++){   // loops row of mat2 and sums product
                result[i][j] += mult1[i][k] * mult2[k][j];
            }
        }
    }
    return result;
}

int main(void){
    srand (time(NULL));

    // generates 2 random matrices
    std::vector<std::vector<int>> mat1 = generate_mat(3, 3);
    std::vector<std::vector<int>> mat2 = generate_mat(3, 3);
    
    // multiplies the 2 matrices
    std::vector<std::vector<int>> result = mult_mat(mat1, mat2);

    // prints the matrices
    print_mat(mat1);
    print_mat(mat2);
    print_mat(result);
}

