#include "HashOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>

namespace operation {

    HashOperation::HashOperation(uint32_t hashCode, uint32_t result)
    : Operation(hashCode),
    _result(result) {}

    void HashOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        // opening the output file using ofstream
        std::ofstream outputFile(outputPath, std::ios::out | std::ios::trunc);
        
        // checking if an error has occured while opening the file
        if (!outputFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // writing the result to the file in the cache
        outputFile << _result;

        // closing the ofstream
        outputFile.close();

    }

    void HashOperation::addOperationFileToCache() const {
        // opening the cache file using ofstream
        std::ofstream cacheFile("cache/" + getHashCode(), std::ios::out | std::ios::trunc);

        // checking if an error has occured while opening the file
        if (!cacheFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // writing the result to the file in the cache
        cacheFile << _result;

        // closing the ofstream
        cacheFile.close();
    }
}