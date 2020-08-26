#pragma once

#include "Matrix.h" 
#include <cstdint>

namespace matrix {
    
    /**
     * @brief This class defines a matrix and its general behavior.
     */
    class Matrix {
        
        // a pointer to struct matrix
        PMatrix _decorated;

        public:   

            /**
             * @brief The default constructor
             * 
             */
            Matrix() = default;

            /**
             * @brief The first constructor, that creates matrix by height and width
             * 
             * @param height the height of the new matrix
             * @param width the width of the new matrix
             */
            Matrix(uint32_t height, uint32_t width);    
            
            /**
             * @brief The copy constructor
             * 
             * @param other the matrix which is copied to create the new matrix from it
             */
            Matrix(const Matrix& other);  

            /**
             * @brief The copy assignment operator
             * 
             * @param other the matrix which is copied to the current matrix
             * @return Matrix& a reference to the current matrix object
             */
            Matrix& operator=(const Matrix& other);      

            /**
             * @brief The move constructor
             * 
             * @param other the matrix which is data moved to create the new matrix from it
             */
            Matrix(Matrix&& other) noexcept;       

            /**
             * @brief The move assignment operator
             * 
             * @param other the matrix which is data moved to the current matrix 
             * @return Matrix& a reference to the current matrix object
             */
            Matrix& operator=(Matrix&& other) noexcept;   

            /**
             * @brief The destructor
             */
            ~Matrix(); 

            /**
             * @brief The getter operator
             * 
             * @param rowIndex the row of the item we want to get
             * @param colIndex the column of the item we want to get
             * @return double the value of the item placed in (rowIndex, colIndex)
             */
            double operator()(uint32_t rowIndex, uint32_t colIndex) const;

            /**
             * @brief The setter method
             * 
             * @param val the val we want to set
             * @param rowIndex the row of the item we want to set
             * @param colIndex the column of the item we want to set
             */
            void setAt(uint32_t rowIndex, uint32_t colIndex, double val);

            /**
             * @brief Getter to the matrix height
             * 
             * @return uint32_t the height of the matrix
             */
            uint32_t getHeight() const;

            /**
             * @brief Getter to the matrix width
             * 
             * @return uint32_t the width of the matrix
             */
            uint32_t getWidth() const;

            /**
             * @brief The adding operator for matrices
             * 
             * @param other the matrix we add to the current marix
             * @return Matrix& the sum of the current matrix and the other matrix
             */
            Matrix& operator+(const Matrix& other) const;

            /**
             * @brief The substruction operator for matrices
             * 
             * @param other the matrix we substruct from the current marix
             * @return Matrix& the substruction of the current matrix and the other matrix
             */
            Matrix& operator-(const Matrix& other) const;

            /**
             * @brief The multiplying operator for matrices
             * 
             * @param other the matrix we multiply the current matrix with
             * @return Matrix& the multiplication of the current matrix and the other matrix
             */
            Matrix& operator*(const Matrix& other) const;

            /**
             * @brief The multiplying by scalar operator
             * 
             * @param scalar the scalar we multiply the matrix with
             * @return Matrix& the matrix after multiplying by scalar
             */
            Matrix& operator*(double scalar) const;

            /**
             * @brief Method that turns the matrix by anti clockwise.
             * 
             * @return Matrix& the matrix after the turn
             */
            Matrix& turn();
    };
}