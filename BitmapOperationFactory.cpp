#include "BitmapOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include <string>
#include <fstream>

namespace operation {

    std::unique_ptr<Operation> BitmapOperationFactory::createOperation(const std::vector<std::string>& command,
        cache::CacheManager& cache) const {
        // checking if the command is valid
        if (!isValidCommand(command)) {
            throw exceptions::InvalidCommandException();
        }

        // putting this code in a try block to catch the exception which can be thrown 
        // while creating the bitmap object, and convert it to another exception
        try {
            // getting the input bitmap
            bitmap::Bitmap input(command[2]);

            // getting the hash code of the operation
            uint32_t hashCode = getOperationHashCode(input, command[1]);

            // if the operation is already exist on the cache, we will take the result of the operation
            // from the cache, so we don't have to calculate it again
            if (cache.contains(hashCode)) {
                // getting the result bitmap from the cache
                bitmap::Bitmap result("cache/" + hashCode);
                // returning a unique pointer to the matrix operation
                return std::make_unique<BitmapOperation>(hashCode, result);
            }

            // if the operation isn't on the cache, we will add it to the cache.
            // first, calculating the result bitmap
            bitmap::Bitmap result(input);
            command[1] == "rotate" ? result.turn() : result.gray();
            // getting the operation object
            BitmapOperation operation(hashCode, result);
            // adding the operation object to the cache
            cache.add(operation);
            // returning a smart pointer to the operation
            return std::make_unique<BitmapOperation>(operation);
        } catch (...) {
            // "converting" the exception which was thrown at the ctor of Bitmap while reading from the output file
            // to out FileReadException
            throw exceptions::FileReadException();
        }
    }

    bool BitmapOperationFactory::isValidCommand(const std::vector<std::string>& command) const {
        // checking if the command is valid
        if (command.size() != 4 
        || command[0] != "image" 
        || (command[1] != "rotate" && command[1] != "convert")
        || command[2].substr(command[2].size() - 4, 4) != ".bmp"
        || command[3].substr(command[3].size() - 4, 4) != ".bmp") {
            return false;
        }
        return true;
    }

    uint32_t getOperationHashCode(const bitmap::Bitmap& arg, const std::string& operationType) {

    }
}