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
    };
}