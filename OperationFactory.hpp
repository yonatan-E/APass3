#pragma once

#include "Operation.hpp"
#include <string>

namespace operation {
    
    class OperationFactory {

        public:

            virtual const Operation createOperation(const std::string command[]) const = 0;

        protected:

            virtual bool isValidCommand(const std::string command[]) const = 0;
    };
}