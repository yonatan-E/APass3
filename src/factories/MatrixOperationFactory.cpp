#include "MatrixOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include "CrcHash.hpp"
#include <string>
#include <fstream>
#include <algorithm>

namespace operation {

    std::unique_ptr<Operation> MatrixOperationFactory::createOperation(const std::vector<std::string>& command,
        cache::CacheManager& cache) const {
        
        // checking if the command is valid
        if (command.size() != commandSize || command[0] != firstCommand || (command[1] != secondCommand && command[1] != secondCommandSecond)
        || command[2].find(ext) == std::string::npos || command[3].find(ext) == std::string::npos
        || (command[4].find(ext) == std::string::npos && command[4] != thirdCommand)) {
            throw exceptions::InvalidCommandException();
        }

        // creating a vector with the operation args, which are the operation type and the pathes to the input matrices files
        std::vector<std::string> operationArgs(command.begin() + 1, command.begin() + 4);
        // getting the hash code of the operation
        uint32_t hashCode = calculateOperationHashCode(operationArgs);

        // getting the result matrix
        std::unique_ptr<matrix::Matrix> result;
        // if the operation is already exist on the cache, we will take the result of the operation
        // from the cache, so we don't have to calculate it again.
        if (cache.contains(hashCode)) {
            // getting the result matrix from the cache
            result = std::make_unique<matrix::Matrix>(readMatrixFromFile(cache.getOperationFilePath(hashCode)));

            // if the operation isn't on the cache, we will calculate it and add it to the cache.
        } else {
            // getting the left argument matrix
            auto leftArg = readMatrixFromFile(command[2]);
            // getting the right argument matrix
            auto rightArg = readMatrixFromFile(command[3]);
            // calculating the result matrix
            result = std::make_unique<matrix::Matrix>(command[1] == secondCommand ? leftArg + rightArg : leftArg * rightArg);
        }

        // getting the operation object
        MatrixOperation operation(hashCode, *result);
        // loading the operation object into the cache
        cache.load(operation);
        // returning a smart pointer to the operation
        return std::make_unique<MatrixOperation>(operation);
    }

    uint32_t MatrixOperationFactory::calculateOperationHashCode(const std::vector<std::string>& operationArgs) const {

        // checking if the operation arguments are valid
        if (operationArgs.size() != operationSize || (operationArgs[0] != secondCommand && operationArgs[0] != secondCommandSecond)
        || operationArgs[1].find(ext) == std::string::npos || operationArgs[2].find(ext) == std::string::npos) {
            throw exceptions::InvalidCommandException();
        }

        // getting the left argument matrix
        auto leftArg = readMatrixFromFile(operationArgs[1]);
        // getting the right argument matrix
        auto rightArg = readMatrixFromFile(operationArgs[2]);

        // creating a string to create the hash code from it
        std::string forHash = "";
        for (uint32_t i = 0; i < leftArg.getHeight(); ++i) {
            for (uint32_t j = 0; j < leftArg.getWidth(); ++j) {
                forHash += leftArg(i, j);
            }
        }
        for (uint32_t i = 0; i < rightArg.getHeight(); ++i) {
            for (uint32_t j = 0; j < rightArg.getWidth(); ++j) {
                forHash += rightArg(i, j);
            }
        }

        // adding the operation type to the string
        forHash += operationArgs[0];
            
        // creating a CrcHash object for creating the hashCode
        hash::CrcHash hashTemp(forHash);
        // creating the hashCode code using the crc32 algorithm
        return hashTemp.applyAlgorithm();
    }

    matrix::Matrix MatrixOperationFactory::readMatrixFromFile(const std::string& pathToFile) {
        // opening the matrix file using ifstream
        std::ifstream matrixFile(pathToFile);

        // checking if an error has occured while opening the file
        if (!matrixFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // calculating the number of the rows in the matrix
        uint32_t numRows = 0;
        std::string line;
        while (!matrixFile.eof()) {
            std::getline(matrixFile, line);
            numRows++;
        }
        // getting the ifstream back to the beginning of the file
        matrixFile.seekg(0);

        // calculating the number of the columns in the matrix
        // finding the occurrences number of ',' in the first line to find the number of the 
        // columns from it, because the number of the columns is the number of ',' plus 1.
        std::string firstLine;
        if (!std::getline(matrixFile, firstLine)) {
            // throwing an exception in case that the first line of the file isn't proper,
            // and closing the ifstream first, to prevent a memory leak
            matrixFile.close();
            throw exceptions::FileFormatException();
        }
        uint32_t numColumns = std::count(firstLine.begin(), firstLine.end(), ',') + 1;
        // getting the ifstream back to the beginning of the file
        matrixFile.seekg(0);

        // creating a new matrix with sizes numRows * numColumns
        matrix::Matrix matrix(numRows, numColumns);
        // reading from the file and filling the matrix
        for (uint32_t i = 0; i < numRows; ++i) {
            std::string line;
            if (!getline(matrixFile, line)) {
                // throwing an exception in case that the current line of the file isn't proper,
                // and closing the ifstream first, to prevent a memory leak
                matrixFile.close();
                throw exceptions::FileFormatException();
            }
            // removing the spaces from the line string
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
            // j will run on the string line, colIndex will run on the matrix columns
            uint32_t j = 0, colIndex = 0;
            // iterating over the line string and initializing the matrix
            while (j < line.size()) {
                size_t k = line.find(',', j);
                // if k == npos, it means that there aren't more ',' in the line, so the current number
                // is the last number in the line
                if (k == std::string::npos) {
                    k = line.size();
                }
                // setting the value in the matrix
                try {
                    matrix.setAt(i, colIndex, std::stoi(line.substr(j, k - j + 1)));
                } catch (...) {
                    // throwing a file format exception in case that the stoi function hasn't succeeded
                    throw exceptions::FileFormatException();
                }
                j = k + 1;
                colIndex++;
            }
        }

        // closing the ifstream
        matrixFile.close();

        // returning the matrix
        return matrix;
    }
}