#include "Operation.hpp"
#include "Matrix.hpp"

namespace operation {

    class MatrixOperation : public Operation {
        
        // the left operand matrix
        Matrix _leftOperand;
        // the right operand matrix
        Matrix _rightOperand;
        // the output matrix
        Matrix _output;

        MatrixOperation(std::string info, const Matrix& leftOperand, const Matrix& rightOperand, const Matrix& output);

        virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

        virtual void addOperationFileToCache() const override;
    }
}