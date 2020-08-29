#include "MatrixOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <iostream>

namespace operation {
    
    MatrixOperation::MatrixOperation(uint32_t hashCode, const matrix::Matrix& result)
    : Operation(hashCode), 
    _result(result) {}

    void MatrixOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        // if the outputPath is "stdout", writing to the screen
        if (outputPath == "stdout") {
            std::cout << _result;
            // else, writing to the file in outputPath
        } else {
            // opening the output file using ofstream
            std::ofstream outputFile(outputPath);
            
            // checking if an error has occured while opening the file
            if (!outputFile.is_open()) {
                throw exceptions::FileOpenException();
            }

            // writing the result matrix into the output file
            outputFile << _result;

            // closing the ofstream
            outputFile.close();
        }
    }

    void MatrixOperation::addOperationFileToCache() const {
        // opening the cache file using ofstream
        std::ofstream cacheFile("cache/" + getHashCode());
        
        // checking if an error has occured while opening the file
        if (!cacheFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // writing the result matrix into the cache file
        cacheFile << _result;

        // closing the ofstream
        cacheFile.close();
    }
}