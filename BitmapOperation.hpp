#pragma once

#include "Operation.hpp"
#include "Bitmap.hpp"

namespace operation {

    class BitmapOperation : public Operation {

        public:

            BitmapOperation(uint32_t hashCode, const bitmap::Bitmap& result);

            virtual void writeOperationToFile(const std::string& filePath) const override;

        private:

            // the result bitmap of the operation
            bitmap::Bitmap _result;
    };
}