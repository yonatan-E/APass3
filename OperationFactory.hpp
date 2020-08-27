#pragma once

#include "Operation.hpp"
#include <string>
#include <memory>

namespace operation {
    
    class OperationFactory {

        public:

            virtual std::unique_ptr<Operation> createOperation(const std::string command[]) const = 0;

        protected:

            virtual bool isValidCommand(const std::string command[]) const = 0;
    };
}