#include "HashOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <iostream>

namespace operation {

    HashOperation::HashOperation(uint32_t hashCode, uint32_t result)
    : Operation(hashCode),
    _result(result) {}

    void HashOperation::writeOperationToFile(const std::string& filePath) const {
        // if the given file path is "stdout", writing to the screen
        if (filePath == "stdout") {
            std::cout << _result;
            // else, writing to the file
        } else {
            // opening the file using ofstream
            std::ofstream file(filePath, std::ios::trunc);
            
            // checking if an error has occured while opening the file
            if (!file.is_open()) {
                throw exceptions::FileOpenException();
            }

            // writing the result to the file
            file << _result;

            // closing the ofstream
            file.close();
        }
    }
}