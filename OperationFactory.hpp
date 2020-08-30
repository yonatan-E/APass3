#pragma once

#include "Operation.hpp"
#include "CacheManager.hpp"
#include <string>
#include <vector>
#include <memory>

namespace operation {
    
    /**
     * @brief This class is an abstract operation factory. 
     * 
     */
    class OperationFactory {

        public:

            /**
             * @brief Create an operation object
             * 
             * @param command the command to create the operation object from
             * @param cache a cache manager
             * @return std::unique_ptr<Operation> a unique pointer to the operation
             */
            virtual std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const = 0;

        protected:

            /**
             * @brief Check if a command is valid
             * 
             * @param command the given command
             * @return true if the command is valid
             * @return false if the command is invalid
             */
            virtual bool isValidCommand(const std::vector<std::string>& command) const = 0;
    };
}