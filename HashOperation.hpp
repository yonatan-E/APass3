#pragma once

#include "Operation.hpp"
#include "CrcHash.hpp"

namespace operation {

    class HashOperation : public Operation {

            HashOperation(std::string info, const std::string& input);

            virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

            virtual void addOperationFileToCache() const override;

        private:

            hash::CrcHash _input;

    };
}