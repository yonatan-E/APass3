#include "MatrixOperationFactory.hpp"
#include "OperationExceptions.hpp"
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
        // from the cache, so we don't have to calculate it again
        if (cache.contains(hashCode)) {
            // getting the result matrix from the cache
            matrix::Matrix result(std::move(readMatrixFromFile("cache/" + hashCode)));
            // returning a unique pointer to the matrix operation
            return std::make_unique<MatrixOperation>(hashCode, result);
        }

        // if the operation isn't on the cache, we will add it to the cache.
        // first, calculating the result matrix
        matrix::Matrix result = command[1] == "add" ? leftArg + rightArg : leftArg * rightArg;
        // getting the operation object
        MatrixOperation operation(hashCode, result);
        // adding the operation object to the cache
        cache.add(operation);
        // returning a smart pointer to the operation
        return std::make_unique<MatrixOperation>(operation);
    }

    bool MatrixOperationFactory::isValidCommand(const std::vector<std::string>& command) const {
        // checking if the command is valid
        if (command.size() != 5
        || command[0] != "matrix"
        || (command[1] != "add" && command[1] != "multiply")
        || command[2].substr(command[2].size() - 4, 4) != ".txt"
        || command[3].substr(command[3].size() - 4, 4) != ".txt"
        || (command[4].substr(command[4].size() - 4, 4) != ".txt" && command[4] != "stdout")) {
            return false;
        }
        return true;
    }

    uint32_t getOperationHashCode(const matrix::Matrix& leftArg, const matrix::Matrix& rightArg,
        const std::string& operationType) {
            
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