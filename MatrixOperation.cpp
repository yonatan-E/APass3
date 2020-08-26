#include "MatrixOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <cstdint>

namespace operation {
    
    MatrixOperation::MatrixOperation(std::string info, const matrix::Matrix& leftArg, 
        const matrix::Matrix& rightArg, OperationType type)
        : Operation(info), 
        _leftArg(leftArg), 
        _rightArg(rightArg), 
        _type(type) {}

    void MatrixOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        // opening the output file using ofstream
        std::ofstream outputFile(outputPath);
        
        // checking if an error has occured while opening the file
        if (!outputFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        matrix::Matrix result = (_type == OperationType::add) ? _leftArg + _rightArg : _leftArg * _rightArg;

        // writing the result matrix into the output file
        outputFile << result;

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
        cacheFile << _leftArg << '\n';

        // writing the right operand matrix into the cache file
        cacheFile << _rightArg << '\n';
 
        // writing the operation type into the cache file
        if (_type == OperationType::add) {
            cacheFile << "add";
        } else {
            cacheFile << "multiply";
        }

        // closing the ofstream
        cacheFile.close();
    }
}