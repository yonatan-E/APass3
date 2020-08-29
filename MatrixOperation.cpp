#include "MatrixOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <iostream>

namespace operation {
    
    MatrixOperation::MatrixOperation(uint32_t hashCode, const matrix::Matrix& result)
    : Operation(hashCode), 
    _result(result) {}

    void MatrixOperation::writeOperationToFile(const std::string& filePath) const {
        // if the filePath is "stdout", writing to the screen
        if (filePath == "stdout") {
            std::cout << _result;
            // else, writing to the file in filePath
        } else {
            // opening the file using ofstream
            std::ofstream file(filePath, std::ios::trunc);
            
            // checking if an error has occured while opening the file
            if (!file.is_open()) {
                throw exceptions::FileOpenException();
            }

            // writing the result matrix into the file
            file << _result;

            // closing the ofstream
            file.close();
        }
    }
}