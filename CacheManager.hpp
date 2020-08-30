#pragma once

#include "Operation.hpp"
#include <vector>
#include <memory>

namespace cache {

    class CacheManager {

        // a vector with the hashCodes of all of the operations in the cache
        std::vector<uint32_t> _hashCodes;
        // the maximum size of the cache
        uint32_t _maxSize;
        // the path to the directory where the cache files will be saved
        std::string _directoryPath;

        public:

            /**
             * @brief Construct a new Cache Manager object
             * 
             * @param maxSize the maximum size of the cache
             * @param directoryPath the path to the directory where the cache files will be saved
             */
            CacheManager(uint32_t maxSize, std::string directoryPath);

            /**
             * @brief Check if the given hashCode exists in the cache
             * 
             * @param hashCode the given hashCode
             * @return true if the given hashCode exists in the cache
             * @return false if the given hashCode doesn't exist in the cache
             */
            bool contains(uint32_t hashCode) const;
            void load(const operation::Operation& operation);
            std::string getOperationFilePath(uint32_t hashCode);
    };
}