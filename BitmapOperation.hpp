#pragma once

#include "Operation.hpp"
#include "Bitmap.hpp"

namespace operation {

    class BitmapOperation : public Operation {

        public:

            enum class OperationType {
                rotate,
                convert
            };

            BitmapOperation(const bitmap::Bitmap& input, OperationType type);

            virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

            virtual void addOperationFileToCache() const override;

        private:

            // the input bitmap file
            bitmap::Bitmap _input;
            // the operation type
            OperationType _type;
    };
}