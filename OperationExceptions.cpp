#include "OperationExceptions.hpp"
#include <stdexcept>

namespace operation {
    namespace exceptions {
        
        FileDeleteException::FileDeleteException()
            : std::runtime_error("Error while deleting file") {}

        FileOpenException::FileOpenException()
            : std::runtime_error("Error while opening file") {}

        FileWriteException::FileWriteException()
            : std::runtime_error("Error while writing to file") {}

        FileReadException::FileReadException()
            : std::runtime_error("Error while reading from file") {}

        FileFormatException::FileFormatException()
            : std::runtime_error("Invalid file format") {}

        InvalidCommandException::InvalidCommandException()
            : std::runtime_error("Invalid command") {}
    }
}