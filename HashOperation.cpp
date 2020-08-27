#include "HashOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>

namespace operation {

    HashOperation::HashOperation(const hash::CrcHash& input) : _input(input) {}

    void HashOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        // opening the output file using ofstream
        std::ofstream outputFile(outputPath);
        
        // checking if an error has occured while opening the file
        if (!outputFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // writing the result to the file
        outputFile << _input.applyAlgorithm();

        // closing the ofstream
        outputFile.close();

    }

    void HashOperation::addOperationFileToCache() const {
        // opening the cache file using ofstream
        std::ofstream cacheFile(getCachePath());

        // checking if an error has occured while opening the file
        if (!cacheFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // writing the input to the file in the cache
        cacheFile << _input.getInput();
    }
}