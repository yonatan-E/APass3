#include "HashOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include "CrcHash.hpp"
#include <fstream>
#include <iterator>

namespace operation {

    std::unique_ptr<Operation> HashOperationFactory::createOperation(const std::vector<std::string>& command,
            cache::CacheManager& cache) const {

        // checking if the command is valid
        if (command.size() != commandSize || command[0] != firstCommand || command[1] != secondCommand) {
            throw exceptions::InvalidCommandException();
        }

        // creating a vector with the operation args, which are only the path to the input bin file
        std::vector<std::string> operationArgs(command.begin() + 1, command.begin() + 3);
         
        uint32_t hashCode = calculateOperationHashCode(operationArgs);

        
        uint32_t result;
        // if the operation is already exist on the cache, we will take the result of the operation
        // from the cache, so we don't have to calculate it again
        if (cache.contains(hashCode)) {
            // opening the cache file using ifstream
            std::ifstream cacheFile(cache.getOperationFilePath(hashCode));

            if (!cacheFile.is_open()) {
                throw exceptions::FileOpenException();
            }

            cacheFile >> result;

            // if the operation isn't on the cache, we will calculate it and add it to the cache.
        } else {
            auto input = readCrcHashFromFile(command[2]);
            result = input.applyAlgorithm();
        }

        HashOperation operation(hashCode, result);
        
        cache.load(operation);
        
        return std::make_unique<HashOperation>(operation);
    }

    uint32_t HashOperationFactory::calculateOperationHashCode(const std::vector<std::string>& operationArgs) const {

        // checking if the operation arguments are valid
        if (operationArgs.size() != operationSize || operationArgs[0] != secondCommand) {
            throw exceptions::InvalidCommandException();
        }

        auto input = readCrcHashFromFile(operationArgs[1]);
        
        hash::CrcHash hashTemp(input.getInput() + operationArgs[0]);
        
        return hashTemp.applyAlgorithm();
    }

    hash::CrcHash HashOperationFactory::readCrcHashFromFile(const std::string& pathToFile) {
        
        std::ifstream hashFile(pathToFile, std::ios::binary);

        if (!hashFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        auto content = std::string{std::istreambuf_iterator<char>{hashFile}, std::istreambuf_iterator<char>{}};

        if (!hashFile) {
            throw exceptions::FileReadException();
        }
        
        hash::CrcHash hash(content);

        return hash;   
    }
}