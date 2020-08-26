#include "HashOperation.hpp"
#include "OperationExceptions.hpp"
#include "fstream"

namespace operation{

    HashOperation::HashOperation(std::string info, const hash::CrcHash& input)
    :Operation(info),
    _input(input){}

    void HashOperation::writeOperationToOutputFile(const std::string& outputPath) const{

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





}