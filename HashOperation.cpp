#include "HashOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>

namespace operation {

    HashOperation::HashOperation(const hash::CrcHash& input) : _input(input) {}

    void HashOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        // opening the output file using ofstream
        std::ofstream outputFile(outputPath, std::ios::binary | std::ios::trunc);
        
        // checking if an error has occured while opening the file
        if (!outputFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // writing the output to the file in the cache
        outputFile.write(_input.getInput().data(), static_cast<std::streamsize>(_input.getInput().length()));

        // checking if an error has occured while writing to the file
        if (!outputFile) {
            throw exceptions::FileWriteException();
        }

        // closing the ofstream
        outputFile.close();

    }

    void HashOperation::addOperationFileToCache() const {
        // opening the cache file using ofstream
        std::ofstream cacheFile(getCachePath(), std::ios::binary | std::ios::trunc);

        // checking if an error has occured while opening the file
        if (!cacheFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // writing the input to the file in the cache
        cacheFile.write(_input.getInput().data(), static_cast<std::streamsize>(_input.getInput().length()));

        // checking if an error has occured while writing to the file
        if (!cacheFile) {
            throw exceptions::FileWriteException();
        }

        // line seperator
        cacheFile << '\n';

        // writing the result to the file in the cache
        cacheFile.write(_input.applyAlgorithm().data(), static_cast<std::streamsize>(_input.applyAlgorithm().length()));

        // checking if an error has occured while writing to the file
        if (!cacheFile) {
            throw exceptions::FileWriteException();
        }

        // closing the ofstream
        cacheFile.close();
    }
}