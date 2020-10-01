#include "MatrixOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <iostream>

namespace operation {
    
    MatrixOperation::MatrixOperation(const uint32_t hashCode, const matrix::Matrix& result)
    : Operation(hashCode), 
    m_result(result) {}

    void MatrixOperation::writeOperationToFile(const std::string& filePath) const {
        if (filePath == "stdout") {
            std::cout << m_result << std::endl;
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