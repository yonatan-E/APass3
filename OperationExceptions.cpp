#include "OperationExceptions.hpp"
#include <stdexcept>

namespace operation {
    namespace exceptions {
        
        FileDeleteException::FileDeleteException() 
            : std::runtime_error("Error while deleting file") {}

        FileOpenException::FileOpenException() 
            : std::runtime_error("Error while opening file") {}
    }
}