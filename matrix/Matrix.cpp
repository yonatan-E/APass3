#include "Matrix.hpp"
#include "ErrorCode.hpp"
#include <utility>
#include <cstdint>

namespace matrix {
    
    Matrix::Matrix(uint32_t height, uint32_t width) {
<<<<<<< HEAD
        ErrorCode error = matrix_create(&_decorated, height, width);
=======
        ErrorCode error = matrix_create(&this->_decorated, height, width);
>>>>>>> c_bitmap_factory
        if (!error_isSuccess(error)) {
            throw Exception(error);
        }
    }

    Matrix::Matrix(const Matrix& other) {
<<<<<<< HEAD
        ErrorCode error = matrix_copy(&_decorated, other._decorated);
=======
        ErrorCode error = matrix_copy(&this->_decorated, other._decorated);
>>>>>>> c_bitmap_factory
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
<<<<<<< HEAD
        _decorated = std::exchange(other._decorated, nullptr);
=======
        this->_decorated = std::exchange(other._decorated, nullptr);
>>>>>>> c_bitmap_factory
    }

    Matrix& Matrix::operator=(Matrix&& other) noexcept {
        if (this == &other) {
            return *this;
        }

<<<<<<< HEAD
        matrix_destroy(_decorated);
	    _decorated = std::exchange(other._decorated, nullptr);
=======
        matrix_destroy(this->_decorated);
	    this->_decorated = std::exchange(other._decorated, nullptr);
>>>>>>> c_bitmap_factory
	    return *this;
    }   

    Matrix::~Matrix() {
<<<<<<< HEAD
        matrix_destroy(_decorated);
=======
        matrix_destroy(this->_decorated);
>>>>>>> c_bitmap_factory
    }

    double Matrix::operator()(uint32_t rowIndex, uint32_t colIndex) const {
        double val;
<<<<<<< HEAD
        ErrorCode error = matrix_getValue(_decorated, rowIndex, colIndex, &val);
=======
        ErrorCode error = matrix_getValue(this->_decorated, rowIndex, colIndex, &val);
>>>>>>> c_bitmap_factory
        if (!error_isSuccess(error)) {
            throw Exception(error);
        }
        return val;
    }

    void Matrix::setAt(uint32_t rowIndex, uint32_t colIndex, double val) {
<<<<<<< HEAD
        ErrorCode error = matrix_setValue(_decorated, rowIndex, colIndex, val);
=======
        ErrorCode error = matrix_setValue(this->_decorated, rowIndex, colIndex, val);
>>>>>>> c_bitmap_factory
        if (!error_isSuccess(error)) {
            throw Exception(error);
        }
    }

    uint32_t Matrix::getHeight() const {
        uint32_t height;
<<<<<<< HEAD
        ErrorCode error = matrix_getHeight(_decorated, &height);
=======
        ErrorCode error = matrix_getHeight(this->_decorated, &height);
>>>>>>> c_bitmap_factory
        if (!error_isSuccess(error)) {
            throw Exception(error);
        }
        return height;
    }

    uint32_t Matrix::getWidth() const {
        uint32_t width;
<<<<<<< HEAD
        ErrorCode error = matrix_getWidth(_decorated, &width);
=======
        ErrorCode error = matrix_getWidth(this->_decorated, &width);
>>>>>>> c_bitmap_factory
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
        for (uint32_t i = 0; i < getHeight(); i++) {
            for (uint32_t j = 0; j < getWidth(); j++) {
                if ((*this)(i, j) != other(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    Matrix Matrix::operator+(const Matrix& other) const {
        Matrix sum(getHeight(), getWidth());
        ErrorCode error = matrix_add(&sum._decorated, _decorated, other._decorated);
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
        ErrorCode error = matrix_multiplyMatrices(&mult._decorated, _decorated, other._decorated);
         if (!error_isSuccess(error)) {
            throw Exception(error);
        }
        return mult;
    }

    Matrix Matrix::operator*(double scalar) const {
        Matrix multByScalar(*this);
        ErrorCode error = matrix_multiplyWithScalar(multByScalar._decorated, scalar);
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
        for (uint32_t i = 0; i < matrix.getHeight(); i++) {
            for (uint32_t j = 0; j < matrix.getWidth(); j++) {
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