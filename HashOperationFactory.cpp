#include "HashOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include "Operation.hpp"
#include "HashOperation.hpp"
#include "CrcHash.hpp"
#include <fstream>
#include <iterator>

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
        if (cache.contains(hashCode)) {
            // getting the result hash code from the cache
            uint32_t result;

            // opening the cache file using ifstream
            std::ifstream cacheFile("cache/" + hashCode);

            // checking if an error has occured while opening the file
            if (!cacheFile.is_open()) {
                throw exceptions::FileOpenException();
            }

            // reading the result hash code into var result
            cacheFile >> result;

            // returning a unique pointer to the hash operation
            return std::make_unique<HashOperation>(hashCode, result);
        }

        // if the operation isn't on the cache, we will add it to the cache.
        // getting the operation object
        HashOperation operation(hashCode, input.applyAlgorithm());
        // adding the operation object to the cache
        cache.add(operation);
        // returning a smart pointer to the operation
        return std::make_unique<HashOperation>(operation);
    }

    bool HashOperationFactory::isValidCommand(const std::vector<std::string>& command) const {
        // checking if the command is valid
        if (command.size() != 4 
        || command[0] != "hash" 
        || command[1] != "crc32"
        || command[2].substr(command[2].size() - 4, 4) != ".bin"
        || (command[3].substr(command[3].size() - 4, 4) != ".bin" && command[3] != "stdout")) {
            return false;
        }
        return true;
    }

    uint32_t HashOperationFactory::getOperationHashCode(const hash::CrcHash& arg) {

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

        // returning the hash object
        return hash;   
    }

}