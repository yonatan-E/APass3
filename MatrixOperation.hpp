#pragma once

#include "Operation.hpp"
#include "Matrix.hpp"

namespace operation {

    class MatrixOperation : public Operation {
        
        // the left operand matrix
        matrix::Matrix _leftOperand;
        // the right operand matrix
        matrix::Matrix _rightOperand;
        // the output matrix
        matrix::Matrix _result;

        MatrixOperation(std::string info, const matrix::Matrix& leftOperand, 
            const matrix::Matrix& rightOperand, const matrix::Matrix& result);

        virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

        virtual void addOperationFileToCache() const override;
    }
}