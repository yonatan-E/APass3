#pragma once

#include "OperationFactory.hpp"
#include "BitmapOperation.hpp"

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

        private:

            /**
             * @brief Get the hashCode of the bitmap operation
             * 
             * @param arg the bitmap argument
             * @param operationType the operation type ("rotate" or "convert")
             * @return uint32_t the hashCode of the operation
             */
            static uint32_t getOperationHashCode(const bitmap::Bitmap& arg, const std::string& operationType);

            /**
             * @brief Read a bitmap object from a file
             * 
             * @param pathToFile the file path
             * @return bitmap::Bitmap the bitmap which was read from the file
             */
            static bitmap::Bitmap readBitmapFromFile(const std::string& pathToFile);
    };
}