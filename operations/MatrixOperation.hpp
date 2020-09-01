#pragma once

#include "Operation.hpp"
#include "Matrix.hpp"
#include <fstream>
#include <cstdint>

namespace operation {

    /**
     * @brief This class represents a matrix operation, which has a result and a hashCode.
            A matrix operation can be add or multiply two matrices.
     * 
     */
    class MatrixOperation : public Operation {

        public:

            /**
             * @brief Construct a new Matrix Operation object
             * 
             * @param hashCode the hashCode of the operation
             * @param result the result matrix of the operation
             */
            MatrixOperation(uint32_t hashCode, const matrix::Matrix& result);

            /**
             * @brief Write the result of the operation to a file
             * 
             * @param filePath the file path
             */
            virtual void writeOperationToFile(const std::string& filePath) const override;

        private:

            // the result matrix of the operation (add or multiply)
            matrix::Matrix m_result;
    };
}