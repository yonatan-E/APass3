#include "MatrixOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <cstdint>

namespace operation {
    
    MatrixOperation::MatrixOperation(std::string info, const matrix::Matrix& leftOperand, 
        const matrix::Matrix& rightOperand, const matrix::Matrix& result)
        : Operation(info), 
        _leftOperand(leftOperand), 
        _rightOperand(rightOperand), 
        _result(result) {}

    void MatrixOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        // opening the output file using ofstream
        std::ofstream outputFile(outputPath);
        
        // checking if an error has occured while opening the file
        if (!outputFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // writing the result matrix into the output file
        for (uint32_t i = 0; i < _result.getHeight(); i++) {
            for (uint32_t j = 0; j < _result.getWidth(); j++) {
                outputFile << _result(i, j);
                if (j != _result.getWidth() - 1) {
                    outputFile << ",";
                }
            }
            outputFile << '\n';
        }

        // closing the ofstream
        outputFile.close();
    }
}