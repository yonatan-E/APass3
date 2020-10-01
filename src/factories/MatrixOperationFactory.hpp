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

        const uint32_t commandSize = 5;
        const uint32_t operationSize = 3;
        const std::string firstCommand = "matrix";
        const std::string secondCommand = "add";
        const std::string secondCommandSecond = "multiply";
        const std::string thirdCommand = "stdout";
        const std::string ext = ".txt";

        public:

            /**
             * @brief Create an operation object according to a command
             * 
             * @param command the command to create the operation object from
             * @param cache a cache manager
             * @return std::unique_ptr<Operation> a unique pointer to the operation
             */
            std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const override;

            /**
             * @brief Get the hashCode of an operation
             * 
             * @param operationArgs the operation args:
             *                      operationArgs[0] - the operation type, can be "add" or "multiply"
             *                      operationArgs[1] - the path to the left argument matrix file
             *                      operationArgs[2] - the path to the right argument matrix file
             * @return uint32_t the hashCode of the operation
             */
            uint32_t calculateOperationHashCode(const std::vector<std::string>& operationArgs) const override;

        private:

            /**
             * @brief Read a matrix from a file
             * 
             * @param pathToFile the file path
             * @return matrix::Matrix the matrix which was read from the file
             */
            static matrix::Matrix readMatrixFromFile(const std::string& pathToFile);
    };
}