#pragma once

#include "CacheManager.hpp"
#include <string>
#include <cstdint>

namespace operation {

    class Operation {

        // the hash code of the operation
        uint32_t _hashCode;

        public:

            Operation(uint32_t hashCode);

            virtual ~Operation() = default;

            virtual void writeOperationToFile(const std::string& filePath) const = 0;

            virtual void addOperationFileToCache(const cache::CacheManager& cache) const final;

            virtual uint32_t getHashCode() const final;
    };
}