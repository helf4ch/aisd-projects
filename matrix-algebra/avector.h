#pragma once

#include <vector>

namespace MatrixAlgebra {
    template <typename T>
    class AVector {
    private:
        std::vector<T> avector;
        int dim;

    public:
        explicit AVector(std::vector<T> new_avector, int new_dim) {
            if (new_avector.size() != new_dim) {
                throw "Vector is must be a size of dimension.";
            }
            dim = new_dim;
            avector = new_avector;
        }

        explicit AVector<T>(int new_dim) {
            dim = new_dim;
            avector = std::vector<T>(dim);
        }

        explicit AVector<T>() {
            dim = 0;
            avector = std::vector<T>();
        }

        int GetDim() const {
            return dim;
        }

        std::vector<T> GetAVector() const {
            return avector;
        }
    };

    template <typename T>
    AVector<T> operator+(const AVector<T> &lhs, const AVector<T> &rhs) {
        if (lhs.GetDim() != rhs.GetDim()) {
            throw "Vectors must be the same dimension.";
        }

        std::vector<T> lhs_vector = lhs.GetAVector();
        std::vector<T> rhs_vector = rhs.GetAVector();

        std::vector<T> result(lhs.GetDim());
        for (int i = 0; i < lhs.GetDim(); ++i) {
            result[i] = lhs_vector[i] + rhs_vector[i];
        }

        return AVector(result, result.size());
    }

    template <typename T>
    AVector<T> operator+=(const AVector<T> &lhs, const AVector<T> &rhs) {
        return lhs + rhs;
    }

    template <typename T>
    AVector<T> operator-(const AVector<T> &lhs, const AVector<T> &rhs) {
        if (lhs.GetDim() != rhs.GetDim()) {
            throw "Vectors must be the same dimension.";
        }

        std::vector<T> lhs_vector = lhs.GetAVector();
        std::vector<T> rhs_vector = rhs.GetAVector();

        std::vector<T> result(lhs.GetDim());
        for (int i = 0; i < lhs.GetDim(); ++i) {
            result[i] = lhs_vector[i] - rhs_vector[i];
        }

        return AVector(result, result.size());
    }

    template <typename T>
    AVector<T> operator-=(const AVector<T> &lhs, const AVector<T> &rhs) {
        return lhs - rhs;
    }

    template <typename T>
    AVector<T> operator*(const AVector<T> &av, const T num) {
        std::vector<T> av_vector = av.GetAVector();

        std::vector<T> result(av.GetDim());
        for (int i = 0; i < av.GetDim(); ++i) {
            result[i] = av_vector[i] * num;
        }

        return AVector(result, result.size());
    }

    template <typename T>
    AVector<T> operator*(const T num, const AVector<T> &av) {
        std::vector<T> av_vector = av.GetAVector();

        std::vector<T> result(av.GetDim());
        for (int i = 0; i < av.GetDim(); ++i) {
            result[i] = av_vector[i] * num;
        }

        return AVector(result, result.size());
    }

    template <typename T>
    AVector<T> operator*=(const AVector<T> &av, const T num) {
        return av * num;
    }
}
