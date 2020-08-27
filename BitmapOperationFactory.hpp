#pragma once

#include "OperationFactory.hpp"
#include "BitmapOperation.hpp"

namespace operation {

    class BitmapOperationFactory : public OperationFactory {

        public:

            virtual std::unique_ptr<Operation> createOperation(const std::string command[]) const override;

        protected:

            virtual bool isValidCommand(const std::string command[]) const override;
    };
}