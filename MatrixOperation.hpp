#pragma once

#include "Operation.hpp"
#include "Matrix.hpp"
#include <fstream>
#include <cstdint>

namespace operation {

    class MatrixOperation : public Operation {

        public:

            MatrixOperation(uint32_t hashCode, const matrix::Matrix& result);

            virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

            virtual void addOperationFileToCache() const override;

        private:

            // the result matrix of the operation
            matrix::Matrix _result;
    };
}