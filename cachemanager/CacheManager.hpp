#pragma once

#include "../operations/Operation.hpp"
#include <vector>
#include <memory>

namespace cache {

    /**
     * @brief This class represents a cache manager
     * 
     */
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
             * @brief Load the operation into the cache:
                    If the operation doesn't exist on the cache, add it to the cache.
                    If the operation exists on the cache, make it more relevant on the cache.
             * 
             * @param operation the operation to load into the cache
             */
            void load(const operation::Operation& operation);

            /**
             * @brief Check if the given hashCode exists in the cache
             * 
             * @param hashCode the given hashCode
             * @return true if the given hashCode exists in the cache
             * @return false if the given hashCode doesn't exist in the cache
             */
            bool contains(uint32_t hashCode) const;

            /**
             * @brief Clear the cache
             * 
             */
            void clear();

            /**
             * @brief Do a cache command, which can be search or clear
             * 
             * @param command the given command
             */
            void doCommand(const std::vector<std::string>& command);

            /**
             * @brief Get the path of the operation file of the operation with the given hashCode
             * 
             * @param hashCode the given hashCode
             * @return std::string the path to the operation file of the operation with the given hashCode
             */
            std::string getOperationFilePath(uint32_t hashCode) const;
    };
}