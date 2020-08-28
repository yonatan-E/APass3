#include "MatrixOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <cstdint>
#include <iostream>

namespace operation {
    
    MatrixOperation::MatrixOperation(const matrix::Matrix& leftArg, const matrix::Matrix& rightArg, OperationType type)
        :_leftArg(leftArg), 
        _rightArg(rightArg), 
        _type(type) {}

    void MatrixOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        // getting the result matrix
        matrix::Matrix result = (_type == OperationType::add) ? _leftArg + _rightArg : _leftArg * _rightArg;

        // if the outputPath is "stdout", writing to the screen
        if (outputPath == "stdout") {
            std::cout << result;
            // else, writing to the file in outputPath
        } else {
            // opening the output file using ofstream
            std::ofstream outputFile(outputPath);
            
            // checking if an error has occured while opening the file
            if (!outputFile.is_open()) {
                throw exceptions::FileOpenException();
            }

            // writing the result matrix into the output file
            outputFile << result;

            // closing the ofstream
            outputFile.close();
        }
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
            cacheFile << "add" << '\n';
        } else {
            cacheFile << "multiply" << '\n';
        }

        // getting the result matrix
        matrix::Matrix result = (_type == OperationType::add) ? _leftArg + _rightArg : _leftArg * _rightArg;
        // writing the result matrix to the cache file
        cacheFile << result;

        // closing the ofstream
        cacheFile.close();
    }

    bool MatrixOperation::operator==(Operation& other) const {
        try {
            MatrixOperation& otherMatrix = dynamic_cast<MatrixOperation&>(other);
            return this->_leftArg == otherMatrix._leftArg 
            && this->_rightArg == otherMatrix._rightArg
            && this->_type == otherMatrix._type;
        } catch (...) {
            return false;
        }
    }
}