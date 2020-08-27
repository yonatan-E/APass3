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

        std::string result = _input.applyAlgorithm();

        outputFile << result;

        // closing the ofstream
        outputFile.close();

    }

    void HashOperation::addOperationFileToCache() const{

        std::ofstream cacheFile(getCachePath());

         // checking if an error has occured while opening the file
        if (!cacheFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        cacheFile << _input.getInput();
    }
}