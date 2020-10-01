#include "HashOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <iostream>

namespace operation {

    HashOperation::HashOperation(const uint32_t hashCode, const uint32_t result)
    : Operation(hashCode),
    m_result(result) {}

    void HashOperation::writeOperationToFile(const std::string& filePath) const {
        if (filePath == "stdout") {
            std::cout << m_result << '\n';
        } else {
            std::ofstream file(filePath, std::ios::trunc);
            
            if (!file.is_open()) {
                throw exceptions::FileOpenException();
            }

            file << m_result;
            
            file.close();
        }
    }
}