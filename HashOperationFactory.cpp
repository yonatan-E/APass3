#include "HashOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include "Operation.hpp"
#include "HashOperation.hpp"
#include "CrcHash.hpp"
#include <fstream>
#include <iterator>

namespace operation {

    std::unique_ptr<Operation> HashOperationFactory::createOperation(const std::string command[]) const {
        // checking if the command is valid and throwing an exception if it isn't
        if (!isValidCommand(command)) {
            throw exceptions::InvalidCommandException();
        }

        // getting the input crcHash
        hash::CrcHash input(std::move(readHashFromFile(command[2])));

        return std::make_unique<Operation>(input);
    }

    bool HashOperationFactory::isValidCommand(const std::string command[]) const {
        // checking if the command is valid
        if (sizeof(command) / sizeof(std::string) != 4 
        || command[0] != "hash" 
        || command[1] != "crc32"
        || command[2].substr(command[2].size() - 4, 4) != ".bin"
        || (command[3].substr(command[3].size() - 4, 4) != ".bin" && command[3] != "stdout")) {
            return false;
        }
        return true;
    }

    hash::CrcHash HashOperationFactory::readHashFromFile(const std::string& pathToFile) {
        // opening the file using ifstream
        std::ifstream hashFile(pathToFile, std::ios::binary);

        // checking if an error has occured while opening the file
        if (!hashFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // reading the content of the file using iterators
        auto content = std::string{std::istreambuf_iterator<char>{hashFile}, std::istreambuf_iterator<char>{}};

        // checking if an error has occured while reading from file
        if (!hashFile.eof()) {
            throw exceptions::FileReadException();
        }
        
        // creating an hash object from the content of the file
        hash::CrcHash hash(content);

        return std::move(hash);   
    }

}