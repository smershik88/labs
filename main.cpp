#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>

#include "rectangle_matrix.h"

int main() {
    std::ifstream istrm("input.txt", std::ios::binary);
    std::ofstream ostrm("output.txt", std::ios::binary);

    auto matrix_1 = RectangleMatrix::readRectangleMatrix<float>(istrm);
    if (!matrix_1) {
        std::cerr << "Wrong matrix_1 size!\n";
        return EXIT_FAILURE;
    }

    auto matrix_2 = RectangleMatrix::readRectangleMatrix<float>(istrm);
    if (!matrix_2) {
        std::cerr << "Wrong matrix_2 size!\n";
        return EXIT_FAILURE;
    }

    auto result_matrix =
        RectangleMatrix::addRectangleMatrix(matrix_1.value(), matrix_2.value());
    if (!result_matrix) {
        std::cerr << "Matrix sizes must be equal!\n";
        return EXIT_FAILURE;
    }
    RectangleMatrix::printRectangleMatrix(result_matrix.value(), ostrm);

    result_matrix =
        RectangleMatrix::subRectangleMatrix(matrix_1.value(), matrix_2.value());
    if (!result_matrix) {
        std::cerr << "Matrix sizes must be equal!\n";
        return EXIT_FAILURE;
    }
    RectangleMatrix::printRectangleMatrix(result_matrix.value(), ostrm);

    auto matrix_3 = RectangleMatrix::readRectangleMatrix<int>(istrm);
    if (!matrix_3) {
        std::cerr << "Wrong matrix_3 size!\n";
        return EXIT_FAILURE;
    }

    auto transposed_matrix =
        RectangleMatrix::transpositionRectangleMatrix(matrix_3.value());
    RectangleMatrix::printRectangleMatrix(transposed_matrix, ostrm);

    return EXIT_SUCCESS;
}