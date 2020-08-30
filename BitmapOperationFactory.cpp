#include "BitmapOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include "CrcHash.hpp"
#include <string>
#include <fstream>

namespace operation {

    std::unique_ptr<Operation> BitmapOperationFactory::createOperation(const std::vector<std::string>& command,
        cache::CacheManager& cache) const {
        // checking if the command is valid
        if (!isValidCommand(command)) {
            throw exceptions::InvalidCommandException();
        }

        // getting the input bitmap
        bitmap::Bitmap input(std::move(readBitmapFromFile(command[2])));

        // getting the hash code of the operation
        uint32_t hashCode = getOperationHashCode(input, command[1]);

        // if the operation is already exist on the cache, we will take the result of the operation
        // from the cache, so we don't have to calculate it again.
        // if the operation isn't on the cache, we will calculate it and add it to the cache.
        bitmap::Bitmap result = cache.contains(hashCode) ?
        bitmap::Bitmap(std::move(readBitmapFromFile(cache.getOperationFilePath(hashCode))))
        : bitmap::Bitmap(input);
        // calculating the operation in case that it doesn't exist on the cache
        if (!cache.contains(hashCode)) {
            command[1] == "rotate" ? result.turn() : result.gray();
        }

        // getting the operation object
        BitmapOperation operation(hashCode, result);
        // adding the operation object to the cache
        cache.load(operation);
        // returning a smart pointer to the operation
        return std::make_unique<BitmapOperation>(operation);        
    }

    bool BitmapOperationFactory::isValidCommand(const std::vector<std::string>& command) const {
        // checking if the command is valid
        if (command.size() != 4 
        || command[0] != "image" 
        || (command[1] != "rotate" && command[1] != "convert")) {
            return false;
        }
        return true;
    }

    uint32_t BitmapOperationFactory::getOperationHashCode(const bitmap::Bitmap& arg, const std::string& operationType) {
        // creating a string to create the hash code from it
        std::string forHash = arg.getData() + operationType;
        
        // creating crc hash object
        hash::CrcHash hashTemp(forHash);
        // calculating the hash using the crc32 algorithm
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