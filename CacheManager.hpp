#pragma once

#include "Operation.hpp"
#include <vector>

namespace cache {

    class CacheManager {

        std::vector<uint32_t> _hashCodes;
        std::string _pathToInfoFile;

        public:

            CacheManager(uint32_t maxSize, std::string pathToInfoFile);
            bool contains(const operation::Operation& operation);
            void add(const operation::Operation& operation);
    };
}