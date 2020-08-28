#pragma once

#include "Operation.hpp"
#include "CrcHash.hpp"

namespace operation {

    class HashOperation : public Operation {

            HashOperation(const hash::CrcHash& input);

            virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

            virtual void addOperationFileToCache() const override;

            virtual bool operator==(const Operation& other) const;

        private:

            hash::CrcHash _input;
    };
}