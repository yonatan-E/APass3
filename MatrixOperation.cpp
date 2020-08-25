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
        writeMatrixToOfstream(outputFile, _result);

        // closing the ofstream
        outputFile.close();
    }

    void MatrixOperation::addOperationFileToCache() const {
        // opening the cache file using ofstream
        std::ofstream cacheFile(getCachePath());
        
        // checking if an error has occured while opening the file
        if (!cacheFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // writing the left operand matrix into the cache file
        writeMatrixToOfstream(cacheFile, _leftOperand);

        // writing the right operand matrix into the cache file
        writeMatrixToOfstream(cacheFile, _rightOperand);

        // writing the result matrix into the output file
        writeMatrixToOfstream(cacheFile, _result);

        // closing the ofstream
        cacheFile.close();
    }

    void MatrixOperation::writeMatrixToOfStream(std::ofstream& stream, const matrix::Matrix& matrix) {
        // writing the matrix with the stream
        for (uint32_t i = 0; i < matrix.getHeight(); i++) {
            for (uint32_t j = 0; j < matrix.getWidth(); j++) {
                stream << matrix(i, j);
                if (j != matrix.getWidth() - 1) {
                    stream << ",";
                }
            }
            stream << '\n';
        }
        stream << '\n';
    }

}