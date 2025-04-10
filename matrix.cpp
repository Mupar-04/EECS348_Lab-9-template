#include "matrix.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

// Constructor with size
Matrix::Matrix(std::size_t N) : data(N, std::vector<int>(N)), size(N) {}

// Constructor with existing 2D vector
Matrix::Matrix(std::vector<std::vector<int>> nums) : data(std::move(nums)) {
    size = data.size();
}

// Matrix addition
Matrix Matrix::operator+(const Matrix &rhs) const {
    if (size != rhs.size) throw std::invalid_argument("Size mismatch in addition");
    Matrix result(size);
    for (std::size_t i = 0; i < size; ++i)
        for (std::size_t j = 0; j < size; ++j)
            result.data[i][j] = data[i][j] + rhs.data[i][j];
    return result;
}

// Matrix multiplication
Matrix Matrix::operator*(const Matrix &rhs) const {
    if (size != rhs.size) throw std::invalid_argument("Size mismatch in multiplication");
    Matrix result(size);
    for (std::size_t i = 0; i < size; ++i)
        for (std::size_t j = 0; j < size; ++j)
            for (std::size_t k = 0; k < size; ++k)
                result.data[i][j] += data[i][k] * rhs.data[k][j];
    return result;
}

// Set value at (i, j)
void Matrix::set_value(std::size_t i, std::size_t j, int n) {
    if (i >= size || j >= size) throw std::out_of_range("Index out of range");
    data[i][j] = n;
}

// Get value at (i, j)
int Matrix::get_value(std::size_t i, std::size_t j) const {
    if (i >= size || j >= size) throw std::out_of_range("Index out of range");
    return data[i][j];
}

// Get matrix size
int Matrix::get_size() const {
    return static_cast<int>(size);
}

// Sum of main diagonal
int Matrix::sum_diagonal_major() const {
    int sum = 0;
    for (std::size_t i = 0; i < size; ++i)
        sum += data[i][i];
    return sum;
}

// Sum of secondary diagonal
int Matrix::sum_diagonal_minor() const {
    int sum = 0;
    for (std::size_t i = 0; i < size; ++i)
        sum += data[i][size - i - 1];
    return sum;
}

// Swap rows
void Matrix::swap_rows(std::size_t r1, std::size_t r2) {
    if (r1 >= size || r2 >= size) throw std::out_of_range("Row index out of range");
    std::swap(data[r1], data[r2]);
}

// Swap columns
void Matrix::swap_cols(std::size_t c1, std::size_t c2) {
    if (c1 >= size || c2 >= size) throw std::out_of_range("Column index out of range");
    for (std::size_t i = 0; i < size; ++i)
        std::swap(data[i][c1], data[i][c2]);
}

// Print the matrix with alignment
void Matrix::print_matrix() const {
    for (const auto& row : data) {
        for (int val : row)
            std::cout << std::setw(6) << val;
        std::cout << "\n";
    }
}
