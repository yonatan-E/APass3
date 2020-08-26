#pragma once

#include "Operation.hpp"

namespace operation {

    class HashOperation : public Operation {

            HashOperation(std::string info);

            virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

            virtual void addOperationFileToCache() const override;

        private:

    };
}