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

            MatrixOperation(const matrix::Matrix& leftArg, const matrix::Matrix& rightArg, OperationType type);

            virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

            virtual void addOperationFileToCache() const override;

            virtual bool operator==(Operation& other) const override;

        private:

            // the left argument matrix
            matrix::Matrix _leftArg;
            // the right argument matrix
            matrix::Matrix _rightArg;
            // the operation type
            OperationType _type;
    };
}