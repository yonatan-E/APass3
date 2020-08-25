#include <stdexcept>

namespace operation {
    namespace exceptions {

        class FileDeleteException : public std::runtime_error {
            
            public:
                FileDeleteException() 
                    : std::runtime_error("Error while deleting the file") {}
        };
    }
}