#include <stdexcept>

namespace operation {
    namespace exceptions {

        class FileDeleteException : public std::runtime_error {
            
            public:

                FileDeleteException();
        };

        class FileOpenException : public std::runtime_error {
            
            public:
            
                FileOpenException();
        };
    }
}