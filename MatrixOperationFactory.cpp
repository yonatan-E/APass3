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
        if (!isValidCommand(command)) {
            throw exceptions::InvalidCommandException();
        }

        // getting the left argument matrix
        matrix::Matrix leftArg(std::move(readMatrixFromFile(command[2])));
        // getting the right argument matrix
        matrix::Matrix rightArg(std::move(readMatrixFromFile(command[3])));

        // getting the hash code of the operation
        uint32_t hashCode = getOperationHashCode(leftArg, rightArg, command[1]);

        // if the operation is already exist on the cache, we will take the result of the operation
        // from the cache, so we don't have to calculate it again.
        // if the operation isn't on the cache, we will calculate it and add it to the cache.
        matrix::Matrix result = cache.contains(hashCode) ?
        std::move(readMatrixFromFile(cache.getOperationFilePath(hashCode)))
        : (command[1] == "add" ? leftArg + rightArg : leftArg * rightArg);

        // getting the operation object
        MatrixOperation operation(hashCode, result);
        // loading the operation object into the cache
        cache.load(operation);
        // returning a smart pointer to the operation
        return std::make_unique<MatrixOperation>(operation);
    }

    bool MatrixOperationFactory::isValidCommand(const std::vector<std::string>& command) const {
        // checking if the command is valid
        if (command.size() != 5
        || command[0] != "matrix"
        || (command[1] != "add" && command[1] != "multiply")) {
            return false;
        }
        return true;
    }

    uint32_t MatrixOperationFactory::getOperationHashCode(const matrix::Matrix& leftArg, const matrix::Matrix& rightArg,
        const std::string& operationType) {
            // creating a string to create the hash code from it
            std::string forHash = "";
            for (uint32_t i = 0; i < leftArg.getHeight(); i++) {
                for (uint32_t j = 0; j < leftArg.getWidth(); j++) {
                    forHash += leftArg(i, j);
                }
            }
            for (uint32_t i = 0; i < rightArg.getHeight(); i++) {
                for (uint32_t j = 0; j < rightArg.getWidth(); j++) {
                    forHash += rightArg(i, j);
                }
            }
            forHash += operationType;
            
            // creating crc hash object
            hash::CrcHash hashTemp(forHash);
            // creating the hash code using the crc32 algorithm
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
        for (uint32_t i = 0; i < numRows; i++) {
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
                matrix.setAt(i, colIndex, std::stoi(line.substr(j, k - j + 1)));
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