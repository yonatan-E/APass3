#include "HashOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include "Operation.hpp"
#include "HashOperation.hpp"
#include "CrcHash.hpp"
#include <fstream>

namespace operation{

    std::unique_ptr<Operation> HashOperationFactory::createOperation(const std::string command[]) const {

        if (!isValidCommand(command)) {
            throw exceptions::InvalidCommandException();
        }

        return std::make_unique<Operation>(readHashFromFile(command[2]));
    }

    bool HashOperationFactory::isValidCommand(const std::string command[]) const {

        if (command->size() != 4) {
            return false;
        }

        if (command[0] == "hash" != 0) {
            return false;
        }

        if (command[1] == "crc32" != 0) {
            return false;
        }

        return true;
    }

    const hash::CrcHash HashOperationFactory::readHashFromFile(const std::string& pathToFile) {

        std::ifstream hashFile(pathToFile);

        // checking if an error has occured while opening the file
        if (!hashFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        std::string line;
        std::string content = "";
        while (!hashFile.eof()){
            std::getline(hashFile, line);
            content += line;
            content += "\n";
        }

        hash::CrcHash hash(content);

        return std::move(hash);   
    }

}