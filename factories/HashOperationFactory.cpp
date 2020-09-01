#include "HashOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include "CrcHash.hpp"
#include <fstream>
#include <iterator>

namespace operation {

    std::unique_ptr<Operation> HashOperationFactory::createOperation(const std::vector<std::string>& command,
            cache::CacheManager& cache) const {

        // checking if the command is valid
        if (command.size() != 4 || command[0] != "hash" || command[1] != "crc32"
        || command[2].find(".bin") == std::string::npos || command[3].find(".bin") == std::string::npos) {
            throw exceptions::InvalidCommandException();
        }

        // creating a vector with the operation args, which are only the path to the input bin file
        std::vector<std::string> operationArgs(command.begin() + 1, command.begin() + 4);
        // getting the hash code of the operation
        uint32_t hashCode = calculateOperationHashCode(operationArgs);

        // getting the result of the operation
        uint32_t result;
        // if the operation is already exist on the cache, we will take the result of the operation
        // from the cache, so we don't have to calculate it again
        if (cache.contains(hashCode)) {
            // opening the cache file using ifstream
            std::ifstream cacheFile(cache.getOperationFilePath(hashCode));

            // checking if an error has occured while opening the file
            if (!cacheFile.is_open()) {
                throw exceptions::FileOpenException();
            }

            // reading the result hash code into var result
            cacheFile >> result;

            // if the operation isn't on the cache, we will calculate it and add it to the cache.
        } else {
            // getting the input CrcHash
            auto input = readCrcHashFromFile(command[2]);
            // calculating the result hashCode
            result = input.applyAlgorithm();
        }

        // getting the operation object
        HashOperation operation(hashCode, result);
        // loading the operation object into the cache
        cache.load(operation);
        // returning a smart pointer to the operation
        return std::make_unique<HashOperation>(operation);
    }

    uint32_t HashOperationFactory::calculateOperationHashCode(const std::vector<std::string>& operationArgs) const {

        // checking if the operation arguments are valid
        if (operationArgs.size() != 2 || operationArgs[0] != "crc32" || operationArgs[1].find(".bin") == std::string::npos) {
            throw exceptions::InvalidCommandException();
        }

        // getting the input crcHash
        auto input = readCrcHashFromFile(operationArgs[1]);
        
        // creating a CrcHash object for creating the hashCode
        hash::CrcHash hashTemp(input.getInput() + operationArgs[0]);
        // creating the hashCode using the crc32 algorithm
        return hashTemp.applyAlgorithm();
    }

    hash::CrcHash HashOperationFactory::readCrcHashFromFile(const std::string& pathToFile) {
        // opening the file using ifstream
        std::ifstream hashFile(pathToFile, std::ios::binary);

        // checking if an error has occured while opening the file
        if (!hashFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        // reading the content of the file using iterators
        auto content = std::string{std::istreambuf_iterator<char>{hashFile}, std::istreambuf_iterator<char>{}};

        // checking if an error has occured while reading from file
        if (!hashFile) {
            throw exceptions::FileReadException();
        }
        
        // creating an hash object from the content of the file
        hash::CrcHash hash(content);

        // returning the hash object
        return hash;   
    }
}