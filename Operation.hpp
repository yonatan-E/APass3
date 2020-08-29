#pragma once

#include <string>
#include <cstdint>

namespace operation {

    class Operation {

        // the hash code of the operation
        uint32_t _hashCode;

        public:

            Operation(uint32_t hashCode);

            virtual void writeOperationToFile(const std::string& filePath) const = 0;

            virtual void addOperationFileToCache() const = 0;

            virtual void deleteOperationFileFromCache() const final;

            virtual uint32_t getHashCode() const final;
    };
}