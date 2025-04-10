#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "matrix.hpp"

// ---------- TEMPLATE UTILITIES ----------
template <typename T>
void print_matrix(const std::vector<std::vector<T>>& mat) {
    for (const auto& row : mat) {
        for (const auto& val : row)
            std::cout << std::setw(6) << val;
        std::cout << "\n";
    }
}

template <typename T>
void swap_rows(std::vector<std::vector<T>>& mat, std::size_t r1, std::size_t r2) {
    if (r1 < mat.size() && r2 < mat.size()) {
        std::swap(mat[r1], mat[r2]);
    } else {
        std::cerr << "Invalid row indices.\n";
    }
}

template <typename T>
void swap_columns(std::vector<std::vector<T>>& mat, std::size_t c1, std::size_t c2) {
    if (mat.empty() || c1 >= mat[0].size() || c2 >= mat[0].size()) {
        std::cerr << "Invalid column indices.\n";
        return;
    }
    for (auto& row : mat) {
        std::swap(row[c1], row[c2]);
    }
}

template <typename T>
void update_value(std::vector<std::vector<T>>& mat, std::size_t r, std::size_t c, T new_val) {
    if (r < mat.size() && c < mat[0].size()) {
        mat[r][c] = new_val;
    } else {
        std::cerr << "Invalid indices for update.\n";
    }
}

// ---------- MAIN FUNCTION ----------
int main(int argc, char *argv[]) {
  std::string filename;
  std::cout << "Enter input file name: ";
  std::cin >> filename;

  std::ifstream infile(filename);
  if (!infile.is_open()) {
      std::cerr << "Error opening file: " << filename << "\n";
      return 1;
  }


    if (!infile.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    std::size_t N;
    int type_flag;
    infile >> N >> type_flag;

    if (type_flag != 0 && type_flag != 1) {
        std::cerr << "Type flag must be 0 (int) or 1 (double).\n";
        return 1;
    }

    // Load matrix data
    if (type_flag == 0) {
        std::vector<std::vector<int>> mat1(N, std::vector<int>(N));
        std::vector<std::vector<int>> mat2(N, std::vector<int>(N));

        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < N; ++j)
                infile >> mat1[i][j];

        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < N; ++j)
                infile >> mat2[i][j];

        Matrix m1(mat1);
        Matrix m2(mat2);

        std::cout << "Matrix 1:\n"; m1.print_matrix();
        std::cout << "\nMatrix 2:\n"; m2.print_matrix();

        std::cout << "\nMatrix 1 + Matrix 2:\n";
        Matrix m_add = m1 + m2;
        m_add.print_matrix();

        std::cout << "\nMatrix 1 * Matrix 2:\n";
        Matrix m_mul = m1 * m2;
        m_mul.print_matrix();

        std::cout << "\nMatrix 1 Major Diagonal Sum: " << m1.sum_diagonal_major() << "\n";
        std::cout << "Matrix 1 Minor Diagonal Sum: " << m1.sum_diagonal_minor() << "\n";

        // Copy data from Matrix back to vector for polymorphic functions
        auto raw_matrix = mat1;

        // Row swap
        std::size_t r1, r2;
        std::cout << "\nEnter two row indices to swap: ";
        std::cin >> r1 >> r2;
        swap_rows(raw_matrix, r1, r2);
        std::cout << "After row swap:\n";
        print_matrix(raw_matrix);

        // Column swap
        std::size_t c1, c2;
        std::cout << "\nEnter two column indices to swap: ";
        std::cin >> c1 >> c2;
        swap_columns(raw_matrix, c1, c2);
        std::cout << "After column swap:\n";
        print_matrix(raw_matrix);

        // Update value
        std::size_t ur, uc;
        int new_val;
        std::cout << "\nEnter row, column, and new value: ";
        std::cin >> ur >> uc >> new_val;
        update_value(raw_matrix, ur, uc, new_val);
        std::cout << "After value update:\n";
        print_matrix(raw_matrix);
    }
    else if (type_flag == 1) {
        std::vector<std::vector<double>> mat1(N, std::vector<double>(N));
        std::vector<std::vector<double>> mat2(N, std::vector<double>(N));

        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < N; ++j)
                infile >> mat1[i][j];

        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < N; ++j)
                infile >> mat2[i][j];

        std::cout << "Matrix 1:\n"; print_matrix(mat1);
        std::cout << "\nMatrix 2:\n"; print_matrix(mat2);

        // Row swap
        std::size_t r1, r2;
        std::cout << "\nEnter two row indices to swap: ";
        std::cin >> r1 >> r2;
        swap_rows(mat1, r1, r2);
        std::cout << "After row swap:\n";
        print_matrix(mat1);

        // Column swap
        std::size_t c1, c2;
        std::cout << "\nEnter two column indices to swap: ";
        std::cin >> c1 >> c2;
        swap_columns(mat1, c1, c2);
        std::cout << "After column swap:\n";
        print_matrix(mat1);

        // Update value
        std::size_t ur, uc;
        double new_val;
        std::cout << "\nEnter row, column, and new value: ";
        std::cin >> ur >> uc >> new_val;
        update_value(mat1, ur, uc, new_val);
        std::cout << "After value update:\n";
        print_matrix(mat1);
    }

    return 0;
}
