#include "HashOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <iostream>

namespace operation {

    HashOperation::HashOperation(const uint32_t hashCode, const uint32_t result)
    : Operation(hashCode),
    m_result(result) {}

    void HashOperation::writeOperationToFile(const std::string& filePath) const {
        // if the given file path is "stdout", writing to the screen
        if (filePath == "stdout") {
            std::cout << m_result << '\n';
            // else, writing to the file
        } else {
            // opening the file using ofstream
            std::ofstream file(filePath, std::ios::trunc);
            
            // checking if an error has occured while opening the file
            if (!file.is_open()) {
                throw exceptions::FileOpenException();
            }

            // writing the result to the file
            file << m_result;

            // closing the ofstream
            file.close();
        }
    }
}