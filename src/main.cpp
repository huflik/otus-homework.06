#include <iostream>
#include "matrix.h"

int main() {

    Matrix<int, 0> matrix;
    
    for (int i = 0; i < 10; ++i) {
        matrix[i][i] = i;
    }

    for (int i = 0; i < 10; ++i) {
        matrix[i][9 - i] = 9 - i;
    }

    for (int i = 1; i <=8; ++i) {
        for (int j = 1; j <=8; ++j) {
            std::cout << matrix[i][j] << " ";
            
        }
        std::cout << std::endl;
    }

    std::cout << "Количество занятых ячеек: " << matrix.size() << std::endl;

    for (const auto& [pos, value] : matrix) {
        std::cout << "[" << pos.first << "," << pos.second << "] = " << value << std::endl;
    }

    return 0;
}