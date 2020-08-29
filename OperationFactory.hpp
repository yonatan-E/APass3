#pragma once

#include "Operation.hpp"
#include "CacheManager.hpp"
#include <string>
#include <vector>
#include <memory>

namespace operation {
    
    class OperationFactory {

        public:

            virtual std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const = 0;

        protected:

            virtual bool isValidCommand(const std::vector<std::string>& command) const = 0;
    };
}