#pragma once

#include "OperationFactory.hpp"
#include "../operations/BitmapOperation.hpp"

namespace operation {

    /**
     * @brief This class is in charge of creating BitmapOperation objects.
     * 
     */
    class BitmapOperationFactory : public OperationFactory {

        public:

            /**
             * @brief Create an operation object according to a command
             * 
             * @param command the command to create the operation object from
             * @param cache a cache manager
             * @return std::unique_ptr<Operation> a unique pointer to the operation
             */
            virtual std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const override;

            /**
             * @brief Get the hashCode of an operation
             * 
             * @param operationArgs the operation args:
             *                      operationArgs[0] - the operation type, can be "rotate" or "convert"
             *                      operationArgs[1] - the path to the input bitmap file
             * @return uint32_t the hashCode of the operation
             */
            virtual uint32_t calculateOperationHashCode(const std::vector<std::string>& operationArgs) const override;

        private:

            /**
             * @brief Read a bitmap object from a file
             * 
             * @param pathToFile the file path
             * @return bitmap::Bitmap the bitmap which was read from the file
             */
            static bitmap::Bitmap readBitmapFromFile(const std::string& pathToFile);
    };
}