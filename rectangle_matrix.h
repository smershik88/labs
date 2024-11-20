#ifndef __RECTANGLE_MATRIX_H__
#define __RECTANGLE_MATRIX_H__

#include <cstdlib>
#include <iostream>
#include <istream>
#include <optional>
#include <vector>

namespace RectangleMatrix {

template <typename T> using MatrixRow_t = std::vector<T>;
template <typename T> using Matrix_t = std::vector<MatrixRow_t<T>>;

template <typename T>
Matrix_t<T> createRectangleMatrix(const std::size_t n = 0,
                                  const std::size_t m = 0, T initValue = T{}) {
    return Matrix_t<T>(n, MatrixRow_t<T>(m, initValue));
}

template <typename T>
std::optional<Matrix_t<T>>
readRectangleMatrix(std::istream &inputStream = std::cin) {
    std::size_t size_n = 0;
    std::size_t size_m = 0;
    inputStream >> size_n >> size_m;
    if (size_n < 1 || size_m < 1) {
        return std::nullopt;
    }
    Matrix_t<T> matrix = createRectangleMatrix<T>(size_n, size_m);
    for (MatrixRow_t<T> &row : matrix) {
        for (T &element : row) {
            inputStream >> element;
        }
    }
    return matrix;
}

template <typename T>
void printRectangleMatrix(const RectangleMatrix::Matrix_t<T> &matrix,
                          std::ostream &outputStream = std::cout) {
    for (auto &&row : matrix) {
        for (auto &&element : row) {
            outputStream << element << '\t';
        }
        outputStream << '\n';
    }
    outputStream << '\n';
}

template <typename T>
std::optional<Matrix_t<T>> addRectangleMatrix(const Matrix_t<T> &lhs,
                                              const Matrix_t<T> &rhs) {
    if ((lhs.size() != rhs.size()) || (lhs[0].size() != rhs[0].size())) {
        return std::nullopt;
    }
    const std::size_t size_n = lhs.size();
    const std::size_t size_m = lhs[0].size();
    Matrix_t<T> result_matrix{};
    for (std::size_t i = 0; i < size_n; ++i) {
        MatrixRow_t<T> row{};
        for (std::size_t j = 0; j < size_m; ++j) {
            row.push_back(lhs[i][j] + rhs[i][j]);
        }
        result_matrix.push_back(row);
    }
    return result_matrix;
}

template <typename T>
std::optional<Matrix_t<T>> subRectangleMatrix(const Matrix_t<T> &lhs,
                                              const Matrix_t<T> &rhs) {
    if ((lhs.size() != rhs.size()) || (lhs[0].size() != rhs[0].size())) {
        return std::nullopt;
    }
    const std::size_t size_n = lhs.size();
    const std::size_t size_m = lhs[0].size();
    Matrix_t<T> result_matrix{};
    for (std::size_t i = 0; i < size_n; ++i) {
        MatrixRow_t<T> row{};
        for (std::size_t j = 0; j < size_m; ++j) {
            row.push_back(lhs[i][j] - rhs[i][j]);
        }
        result_matrix.push_back(row);
    }
    return result_matrix;
}

template <typename T>
std::optional<Matrix_t<T>> mulRectangleMatrix(const Matrix_t<T> &lhs,
                                              const Matrix_t<T> &rhs) {
    if (lhs[0].size() != rhs.size()) {
        return std::nullopt;
    }
    const std::size_t lhs_rows_cnt = lhs.size();
    const std::size_t rhs_rows_cnt = rhs.size();
    const std::size_t rhs_cols_cnt = rhs[0].size();
    Matrix_t<T> result_matrix =
        createRectangleMatrix<T>(lhs_rows_cnt, rhs_cols_cnt);
    for (std::size_t i = 0; i < lhs_rows_cnt; ++i) {
        for (std::size_t j = 0; j < rhs_cols_cnt; ++j) {
            result_matrix[i][j] = 0;
            for (std::size_t k = 0; k < rhs_rows_cnt; ++k) {
                result_matrix[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return result_matrix;
}

template <typename T>
Matrix_t<T> transpositionRectangleMatrix(const Matrix_t<T> &matrix) {
    const std::size_t size_n = matrix.size();
    const std::size_t size_m = matrix[0].size();
    Matrix_t<T> result_matrix = createRectangleMatrix<T>(size_m);
    for (std::size_t i = 0; i < size_n; ++i) {
        for (size_t j = 0; j < size_m; ++j) {
            result_matrix[j].push_back(matrix[i][j]);
        }
    }
    return result_matrix;
}

} // namespace RectangleMatrix

#endif
