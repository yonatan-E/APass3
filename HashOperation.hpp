#pragma once

#include "Operation.hpp"
#include "CrcHash.hpp"

namespace operation {

    class HashOperation : public Operation {

            HashOperation(uint32_t hashCode, uint32_t result);

            virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

            virtual void addOperationFileToCache() const override;

        private:

            uint32_t _result;
    };
}