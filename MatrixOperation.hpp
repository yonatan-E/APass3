#pragma once

#include "Operation.hpp"
#include "Matrix.hpp"
#include <fstream>

namespace operation {

    class MatrixOperation : public Operation {

        public:
        
            enum class OperationType {
                add,
                multiply
            };

            MatrixOperation(std::string info, const matrix::Matrix& leftArg, 
                const matrix::Matrix& rightArg, OperationType type);

            virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

            virtual void addOperationFileToCache() const override;

        private:

            static void writeMatrixToOfStream(std::ofstream& stream, const matrix::Matrix& matrix);

            // the left argument matrix
            matrix::Matrix _leftArg;
            // the right argument matrix
            matrix::Matrix _rightArg;
            // the operation type
            OperationType _type;
    };
}