#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cstdlib>

template <typename T>
class Matrix {
    T* data;
    std::size_t rows;
    std::size_t cols;

   public:
    Matrix(std::size_t rows, std::size_t cols) : rows(rows), cols(cols) {
        data = new T[rows * cols];
    }

    ~Matrix() {
        delete[] data;
    }

    auto get(std::size_t row, std::size_t col) -> T& {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix out of bounds");
        }
        return data[row * cols + col];
    }

    auto get(std::size_t row, std::size_t col) const -> const T& {
        return data[row * cols + col];
    }

    auto begin() -> T* {
        return data;
    }

    auto end() -> T* {
        return data + rows * cols;
    }

    auto begin() const -> const T* {
        return data;
    }

    auto end() const -> const T* {
        return data + rows * cols;
    }

    auto size() const -> std::size_t {
        return rows * cols;
    }

    auto get_rows() const -> std::size_t {
        return rows;
    }

    auto get_cols() const -> std::size_t {
        return cols;
    }

    auto show() const {
        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < cols; ++j) {
                std::cout << get(i, j).to_string() << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};