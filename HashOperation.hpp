#pragma once

#include "Operation.hpp"
#include "CrcHash.hpp"

namespace operation {

    class HashOperation : public Operation {
        
        public:

            HashOperation(uint32_t hashCode, uint32_t result);

            virtual void writeOperationToFile(const std::string& filePath) const override;

        private:

            uint32_t _result;
    };
}