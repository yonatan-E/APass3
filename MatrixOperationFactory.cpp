#include "MatrixOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdint>

namespace operation {

    const Operation& MatrixOperationFactory::createOperation(const std::string command[]) const {

    }

    bool MatrixOperationFactory::isValidCommand(const std::string command[]) const {
        // checking if the command is valid
        if (sizeof(command) / sizeof(std::string) != 5 
        || command[0] != "matrix" 
        || (command[1] != "add" && command[1] != "multiply")
        || command[2].substr(command[2].size() - 4, 4) != ".txt"
        || command[3].substr(command[3].size() - 4, 4) != ".txt"
        || (command[4].substr(command[2].size() - 4, 4) != ".txt" && command[4] != "stdout")) {
            return false;
        }
        return true;
    }

    const matrix::Matrix MatrixOperationFactory::readMatrixFromFile(const std::string& pathToFile) {
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
            for (uint32_t j = 0; j < numColumns; j += 2) {
                // writing the current value into the matrix
                matrix.setAt(i, j, line.at(j / 2));
            }
        }

        // closing the ifstream
        matrixFile.close();

        return std::move(matrix);
    }
}