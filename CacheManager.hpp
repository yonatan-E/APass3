#pragma once

#include "Operation.hpp"
#include <vector>

namespace cache {

    class CacheManager {

        std::vector<uint32_t> _hashCodes;
        uint32_t _maxSize;
        std::string _pathToInfoFile;

        public:

            CacheManager(uint32_t maxSize, std::string pathToInfoFile);
            bool contains(uint32_t hashCode) const;
            void add(const operation::Operation& operation);
    };
}