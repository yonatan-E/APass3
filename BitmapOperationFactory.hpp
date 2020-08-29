#pragma once

#include "OperationFactory.hpp"
#include "BitmapOperation.hpp"

namespace operation {

    class BitmapOperationFactory : public OperationFactory {

        public:

            virtual std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const override;

        protected:

            virtual bool isValidCommand(const std::vector<std::string>& command) const override;

        private:

            static uint32_t getOperationHashCode(const bitmap::Bitmap& arg, const std::string& operationType);

            static bitmap::Bitmap readBitmapFromFile(const std::string& pathToFile);
    };
}