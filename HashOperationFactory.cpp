#include "HashOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include "Operation.hpp"
#include "HashOperation.hpp"
#include "CrcHash.hpp"
#include <fstream>
#include <iterator>
#include <string>

namespace operation {

    std::unique_ptr<Operation> HashOperationFactory::createOperation(const std::vector<std::string>& command,
            cache::CacheManager& cache) const {

        // checking if the command is valid
        if (!isValidCommand(command)) {
            throw exceptions::InvalidCommandException();
        }

        // getting the input crcHash
        hash::CrcHash input(std::move(readHashFromFile(command[2])));

        // getting the hash code of the operation
        uint32_t hashCode = getOperationHashCode(input);

        // if the operation is already exist on the cache, we will take the result of the operation
        // from the cache, so we don't have to calculate it again
        uint32_t result = cache.contains(hashCode) ?
        std::stoi(readHashFromFile(cache.getOperationFilePath(hashCode)).getInput()) :
        (input.applyAlgorithm());
        
        HashOperation operation(hashCode, result);

         // adding the operation object to the cache
        cache.load(operation);
        // returning a smart pointer to the operation
        return std::make_unique<HashOperation>(operation);
        
    }

    bool HashOperationFactory::isValidCommand(const std::vector<std::string>& command) const {
        // checking if the command is valid
        if (command.size() != 4 
        || command[0] != "hash" 
        || command[1] != "crc32") {
            return false;
        }
        return true;
    }

    uint32_t HashOperationFactory::getOperationHashCode(const hash::CrcHash& arg) {
        hash::CrcHash hashTemp(arg.getInput() + arg.getInput());
        return hashTemp.applyAlgorithm();
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
        
        // creating an hash object from the content of the file
        hash::CrcHash hash(content);

        // returning the hash object
        return hash;   
    }

}