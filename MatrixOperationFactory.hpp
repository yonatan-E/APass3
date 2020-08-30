#pragma once

#include "OperationFactory.hpp"
#include "MatrixOperation.hpp"
#include <cstdint>

namespace operation {

    /**
     * @brief This class is in charge of creating MatrixOperation objects.
     *
     */
    class MatrixOperationFactory : public OperationFactory {

        public:

            /**
             * @brief Create an operation object
             * 
             * @param command the command to create the operation object from
             * @param cache a cache manager
             * @return std::unique_ptr<Operation> a unique pointer to the operation
             */
            virtual std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const override;

        private:

            /**
             * @brief Get the hashCode of a matrix operation
             * 
             * @param leftArg the left matrix argument
             * @param rightArg the right matrix argument
             * @param operationType the operation type ("add" or "multiply")
             * @return uint32_t the hashCode of the operation
             */
            static uint32_t getOperationHashCode(const matrix::Matrix& leftArg, const matrix::Matrix& rightArg,
                const std::string& operationType);

            /**
             * @brief Read a matrix from a file
             * 
             * @param pathToFile the file path
             * @return matrix::Matrix the matrix which was read from the file
             */
            static matrix::Matrix readMatrixFromFile(const std::string& pathToFile);
    };
}