#pragma once

#include "OperationFactory.hpp"
#include "MatrixOperation.hpp"
#include <cstdint>

namespace operation {

    class MatrixOperationFactory : public OperationFactory {

        public:

            virtual std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const override;

        protected:

            virtual bool isValidCommand(const std::vector<std::string>& command) const override;

        private:

            static uint32_t getOperationHashCode(const matrix::Matrix& leftArg, const matrix::Matrix& rightArg,
                const std::string& operationType);

            static matrix::Matrix readMatrixFromFile(const std::string& pathToFile);
    };
}