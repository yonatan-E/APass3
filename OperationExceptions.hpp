#pragma once

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

        class FileWriteException : public std::runtime_error {

            public:

                FileWriteException();
        };

        class FileReadException : public std::runtime_error {

            public:

                FileReadException();
        };

        class FileFormatException : public std::runtime_error {

            public:

                FileFormatException();
        };
    }
}