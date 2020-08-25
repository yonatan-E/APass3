#include "OperationExceptions.hpp"
#include <stdexcept>

namespace operation {
    namespace exceptions {
        FileDeleteException::FileDeleteException() 
            : std::runtime_error("Error while deleting file") {}
    }
}