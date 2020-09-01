#include "Matrix.hpp"
#include "ErrorCode.hpp"
#include <utility>
#include <cstdint>

namespace matrix {
    
    Matrix::Matrix(uint32_t height, uint32_t width) {
        ErrorCode error = matrix_create(&m_delegated, height, width);
        if (!error_isSuccess(error)) {
            throw Exception(error);
        }
    }

    Matrix::Matrix(const Matrix& other) {
        ErrorCode error = matrix_copy(&m_delegated, other.m_delegated);
        if (!error_isSuccess(error)) {
            throw Exception(error);
        }
    }

    Matrix& Matrix::operator=(const Matrix& other) {
        if (this == &other) {
		    return *this;
	    }

	    // Use the copy constructor and move assignment operator
	    *this = Matrix(other); 
	    return *this;
    }

    Matrix::Matrix(Matrix&& other) noexcept {
        m_delegated = std::exchange(other.m_delegated, nullptr);
    }

    Matrix& Matrix::operator=(Matrix&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        matrix_destroy(m_delegated);
	    m_delegated = std::exchange(other.m_delegated, nullptr);
	    return *this;
    }   

    Matrix::~Matrix() {
        matrix_destroy(m_delegated);
    }

    double Matrix::operator()(uint32_t rowIndex, uint32_t colIndex) const {
        double val;
        ErrorCode error = matrix_getValue(m_delegated, rowIndex, colIndex, &val);
        if (!error_isSuccess(error)) {
            throw Exception(error);
        }
        return val;
    }

    void Matrix::setAt(uint32_t rowIndex, uint32_t colIndex, double val) {
        ErrorCode error = matrix_setValue(m_delegated, rowIndex, colIndex, val);
        if (!error_isSuccess(error)) {
            throw Exception(error);
        }
    }

    uint32_t Matrix::getHeight() const {
        uint32_t height;
        ErrorCode error = matrix_getHeight(m_delegated, &height);
        if (!error_isSuccess(error)) {
            throw Exception(error);
        }
        return height;
    }

    uint32_t Matrix::getWidth() const {
        uint32_t width;
        ErrorCode error = matrix_getWidth(m_delegated, &width);
        if (!error_isSuccess(error)) {
            throw Exception(error);
        }
        return width;
    }

    bool Matrix::operator==(const Matrix& other) const {
        // if the matrices don't have the same sizes, they aren't equal
        if (getHeight() != other.getHeight() || getWidth() != other.getWidth()) {
            return false;
        }

        // comparing every element of the matrices
        for (uint32_t i = 0; i < getHeight(); ++i) {
            for (uint32_t j = 0; j < getWidth(); ++j) {
                if ((*this)(i, j) != other(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    Matrix Matrix::operator+(const Matrix& other) const {
        Matrix sum(getHeight(), getWidth());
        ErrorCode error = matrix_add(&sum.m_delegated, m_delegated, other.m_delegated);
         if (!error_isSuccess(error)) {
            throw Exception(error);
        }
        return sum;
    }

    Matrix Matrix::operator-(const Matrix& other) const {
        return *this + other * (-1);
    }

    Matrix Matrix::operator*(const Matrix& other) const {
        Matrix mult(getHeight(), other.getWidth());
        ErrorCode error = matrix_multiplyMatrices(&mult.m_delegated, m_delegated, other.m_delegated);
         if (!error_isSuccess(error)) {
            throw Exception(error);
        }
        return mult;
    }

    Matrix Matrix::operator*(double scalar) const {
        Matrix multByScalar(*this);
        ErrorCode error = matrix_multiplyWithScalar(multByScalar.m_delegated, scalar);
         if (!error_isSuccess(error)) {
            throw Exception(error);
        }
        return multByScalar;
    }

    Matrix& Matrix::turn() {
        Matrix turned(getWidth(), getHeight());
        uint32_t newColumn, newRow = 0;
        for (uint32_t oldColumn = 0; oldColumn < getWidth(); oldColumn++) {
            newColumn = 0;
            for (uint32_t oldRow = 0; oldRow < getHeight(); oldRow++) {
                turned.setAt(getWidth() - newRow - 1, newColumn, (*this)(oldRow, oldColumn));
                newColumn++;
            }
            newRow++;
        }
        *this = std::move(turned);
        return *this;
    }

    std::ostream& operator<<(std::ostream& stream, const Matrix& matrix) {
        // writing the matrix with the stream
        for (uint32_t i = 0; i < matrix.getHeight(); ++i) {
            for (uint32_t j = 0; j < matrix.getWidth(); ++j) {
                stream << matrix(i, j);
                if (j != matrix.getWidth() - 1) {
                    stream << ",";
                }
            }
            if (i < matrix.getHeight() - 1) {
                stream << '\n';
            }
        }
        return stream;
    }
}