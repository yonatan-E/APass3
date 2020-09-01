#pragma once

#include "../operations/Operation.hpp"
#include "../manager/CacheManager.hpp"
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
             * @brief Create an operation object according to a command
             * 
             * @param command the command to create the operation object from
             * @param cache a cache manager
             * @return std::unique_ptr<Operation> a unique pointer to the operation
             */
            virtual std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const = 0;

            /**
             * @brief Get the hashCode of an operation
             * 
             * @param operationArgs the operation args, specific for the operation
             * @return uint32_t the hashCode of the operation
             */
            virtual uint32_t calculateOperationHashCode(const std::vector<std::string>& operationArgs) const = 0;
    };
}