#include "MatrixOperation.hpp"
#include <ofstream>

namespace operation {
    
    MatrixOperation::MatrixOperation(std::string info, const Matrix& leftOperand, 
        const Matrix& rightOperand, const Matrix& output)
        : Operation(info), 
        _leftOperand(leftOperand), 
        _rightOperand(rightOperand), 
        _output(output) {}

    void MatrixOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        
    }
}