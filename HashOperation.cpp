#include "HashOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>

namespace operation {

    HashOperation::HashOperation(uint32_t hashCode, uint32_t result)
    : Operation(hashCode),
    _result(result) {}

    void HashOperation::writeOperationToFile(const std::string& filePath) const {
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