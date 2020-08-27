#include "BitmapOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include <string>
#include <fstream>

namespace operation {

    std::unique_ptr<Operation> BitmapOperationFactory::createOperation(const std::string command[]) const {
        // checking if the command is valid
        if (!isValidCommand(command)) {
            throw exceptions::InvalidCommandException();
        }

        // getting the operation type
        BitmapOperation::OperationType type = command[1] == "rotate" ? 
            BitmapOperation::OperationType::rotate : BitmapOperation::OperationType::convert;
        // getting the input bitmap file
        bitmap::Bitmap input(command[2]);

        return std::make_unique<Operation>(input, type);
    }

    bool BitmapOperationFactory::isValidCommand(const std::string command[]) const {
        // checking if the command is valid
        if (sizeof(command) / sizeof(std::string) != 4 
        || command[0] != "image" 
        || (command[1] != "rotate" && command[1] != "convert")
        || command[2].substr(command[2].size() - 4, 4) != ".bmp"
        || command[3].substr(command[3].size() - 4, 4) != ".bmp") {
            return false;
        }
        return true;
    }
}