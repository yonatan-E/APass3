#include <stdexcept>

namespace operation {
    namespace exceptions {

        class FileDeleteException : public std::runtime_error {
            
            public:
                FileDeleteException();
        };
    }
}