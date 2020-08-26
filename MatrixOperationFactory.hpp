#pragma once

#include "OperationFactory.hpp"
#include "MatrixOperation.hpp"

namespace operation {

    class MatrixOperationFactory : public OperationFactory {

        public:

            virtual const Operation& createOperation(const std::string command[]) const override;

        protected:

            virtual bool isValidCommand(const std::string command[]) const override;

        private:

            static const matrix::Matrix readMatrixFromFile(const std::string& pathToFile);
    };
}