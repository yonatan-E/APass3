#include "BitmapOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include "CrcHash.hpp"
#include <string>
#include <fstream>

namespace operation {

    std::unique_ptr<Operation> BitmapOperationFactory::createOperation(const std::vector<std::string>& command,
        cache::CacheManager& cache) const {
            
        // checking if the command is valid
        if (command.size() != commandSize || command[0] != firstCommand || (command[1] != secondCommand && command[1] != secondCommandSecond) 
        || command[2].find(ext) == std::string::npos || command[3].find(ext) == std::string::npos) {
            throw exceptions::InvalidCommandException();
        }

        // creating a vector with the operation args, which are the operation type and the path to the input bitmap file
        std::vector<std::string> operationArgs(command.begin() + 1, command.begin() + 3);
        // getting the hash code of the operation
        uint32_t hashCode = calculateOperationHashCode(operationArgs);

        // getting the result bitmap
        std::unique_ptr<bitmap::Bitmap> result;
        // if the operation is already exist on the cache, we will take the result of the operation
        // from the cache, so we don't have to calculate it again.
        if (cache.contains(hashCode)) {
            // getting the result bitmap from the cache
            result = std::make_unique<bitmap::Bitmap>(readBitmapFromFile(cache.getOperationFilePath(hashCode)));

            // if the operation isn't on the cache, we will calculate it and add it to the cache.
        } else {
            // getting the input bitmap
            result = std::make_unique<bitmap::Bitmap>(readBitmapFromFile(command[2]));
            // calculating the result bitmap
            command[1] == secondCommand ? result->turn() : result->gray();
        }

        // getting the operation object
        BitmapOperation operation(hashCode, *result);
        // adding the operation object to the cache
        cache.load(operation);
        // returning a smart pointer to the operation
        return std::make_unique<BitmapOperation>(operation);        
    }

    uint32_t BitmapOperationFactory::calculateOperationHashCode(const std::vector<std::string>& operationArgs) const {

        // checking if the operation arguments are valid
        if (operationArgs.size() != operationSize || (operationArgs[0] != secondCommand && operationArgs[0] != secondCommandSecond) 
        || operationArgs[1].find(ext) == std::string::npos) {
            throw exceptions::InvalidCommandException();
        }

        // getting the input bitmap
        auto input = readBitmapFromFile(operationArgs[1]);
        
        // creating a string to create the hash code from it
        std::string forHash = input.getData() + operationArgs[0];
        
        // creating a CrcHash hash object for creating the hashCode
        hash::CrcHash hashTemp(forHash);
        // calculating the hashCode using the crc32 algorithm
        return hashTemp.applyAlgorithm();
    }

    bitmap::Bitmap BitmapOperationFactory::readBitmapFromFile(const std::string& pathToFile) {
        try {
            bitmap::Bitmap bitmap(pathToFile);
            return bitmap;
        } catch (...) {
            // catching the exception which was thrown at the ctor of Bitmap while reading from the file,
            // and converting it to FileReadException.
            throw exceptions::FileReadException();
        }
    }
}