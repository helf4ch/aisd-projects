#pragma once

#include "avector.h"
#include <vector>
#include <iostream>
#include <iomanip>

namespace MatrixAlgebra {
    template <typename T>
    class Matrix {
    private:
        std::vector<AVector<T>> matrix;
        int rows;
        int columns;

    public:
        explicit Matrix(std::vector<AVector<T>> new_matrix, int new_rows, int new_columns) {
            if (new_matrix.size() != new_columns) {
                throw "Vector is must be a size of columns";
            }

            for (auto av : new_matrix) {
                if (av.GetDim() != new_rows) {
                    throw "Dimension of all AVectors must be == rows.";
                }
            }

            matrix = new_matrix;
            rows = new_rows;
            columns = new_columns;
        }

        explicit Matrix(std::vector<std::vector<T>> new_matrix, int new_rows, int new_columns) {
            if (new_matrix.size() != new_rows) {
                throw "Rows is must be == new_rows";
            }

            for (auto v : new_matrix) {
                if (v.size() != new_columns) {
                    throw "Columns of all vectors must be == new_columns.";
                }
            }

            std::vector<AVector<T>> result;
            for (int i = 0; i < new_columns; ++i) {
                std::vector<T> tmp(new_rows);
                for (int j = 0; j < new_rows; ++j) {
                    tmp[j] = new_matrix[j][i];
                }
                AVector<T> tmp_avector(tmp, new_rows);
                result.push_back(tmp_avector);
            }

            matrix = result;
            rows = new_rows;
            columns = new_columns;
        }

        int GetRows() const {
            return rows;
        }

        int GetColumns() const {
            return columns;
        }

        std::vector<AVector<T>> GetMatrix() const {
            return matrix;
        }

        std::vector<std::vector<T>> GetVector() const {
            std::vector<std::vector<T>> result(rows, std::vector<T>(columns));
            
            for (int i = 0; i < columns; ++i) {
                std::vector<T> tmp = matrix[i].GetAVector();
                for (int j = 0; j < rows; ++j) {
                    result[j][i] = tmp[j];
                }
            }

            return result;
        }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream &stream, const Matrix<T> &matrix) {
        std::vector<std::vector<T>> m = matrix.GetVector();

        stream << "rows: " << matrix.GetRows() 
               << ", columns: " << matrix.GetColumns() 
               << '\n'; 

        for (int i = 0; i < matrix.GetRows(); ++i) {
            for (int j = 0; j < matrix.GetColumns(); ++j) {
                stream << std::setw(4) << m[i][j]<< ' '; 
            }
            stream << '\n';
        }

        return stream;
    }

    template <typename T>
    Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs) {
        if (lhs.GetRows() != rhs.GetRows() || lhs.GetColumns() != rhs.GetColumns()) {
            throw "Matrixs must be the same size.";
        }

        std::vector<AVector<T>> lhs_matrix = lhs.GetMatrix();
        std::vector<AVector<T>> rhs_matrix = rhs.GetMatrix();

        std::vector<AVector<T>> result(lhs.GetColumns());
        for (int i = 0; i < lhs.GetColumns(); ++i) {
            result[i] = lhs_matrix[i] + rhs_matrix[i];
        }

        return Matrix(result, lhs.GetRows(), lhs.GetColumns());
    }

    template <typename T>
    Matrix<T> operator+=(const Matrix<T> &lhs, const Matrix<T> &rhs) {
        return lhs + rhs;
    }

    template <typename T>
    Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs) {
        if (lhs.GetRows() != rhs.GetRows() || lhs.GetColumns() != rhs.GetColumns()) {
            throw "Matrixs must be the same size.";
        }

        std::vector<AVector<T>> lhs_matrix = lhs.GetMatrix();
        std::vector<AVector<T>> rhs_matrix = rhs.GetMatrix();

        std::vector<AVector<T>> result(lhs.GetColumns());
        for (int i = 0; i < lhs.GetColumns(); ++i) {
            result[i] = lhs_matrix[i] - rhs_matrix[i];
        }

        return Matrix(result, lhs.GetRows(), lhs.GetColumns());
    }

    template <typename T>
    Matrix<T> operator-=(const Matrix<T> &lhs, const Matrix<T> &rhs) {
        return lhs - rhs;
    }

    template <typename T>
    Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs) {
        if (lhs.GetColumns() != rhs.GetRows()) {
            throw "Columns of first must be == rows of second.";
        }

        std::vector<std::vector<T>> lhs_matrix = lhs.GetVector();
        std::vector<std::vector<T>> rhs_matrix = rhs.GetVector();

        std::vector<std::vector<T>> result(lhs.GetRows(), std::vector<T>(rhs.GetColumns()));
        for (int i = 0; i < lhs.GetRows(); ++i) {
            for (int j = 0; j < lhs.GetColumns(); ++j) {
                for (int k = 0; k < rhs.GetColumns(); ++k) {
                    result[i][k] += lhs_matrix[i][j] * rhs_matrix[j][k];
                }
            }
        }

        return Matrix(result, lhs.GetRows(), rhs.GetColumns());
    }

    template <typename T>
    Matrix<T> operator*(const Matrix<T> &m, const T num) {
        std::vector<AVector<T>> m_matrix = m.GetMatrix();

        std::vector<AVector<T>> result(m.GetColumns());
        for (int i = 0; i < m.GetColumns(); ++i) {
            result[i] = m_matrix[i] * num;
        }

        return Matrix(result, m.GetRows(), m.GetColumns());
    }

    template <typename T>
    Matrix<T> operator*(const T num, const Matrix<T> &m) {
        std::vector<AVector<T>> m_matrix = m.GetMatrix();

        std::vector<AVector<T>> result(m.GetColumns());
        for (int i = 0; i < m.GetColumns(); ++i) {
            result[i] = m_matrix[i] * num;
        }

        return Matrix(result, m.GetRows(), m.GetColumns());
    }

    template <typename T>
    Matrix<T> operator*=(const Matrix<T> &lhs, const Matrix<T> &rhs) {
        return lhs * rhs;
    }

    template <typename T>
    Matrix<T> operator*=(const Matrix<T> &m, const T num) {
        return m * num;
    }
}
