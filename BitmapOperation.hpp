#pragma once

#include "Operation.hpp"
#include "Bitmap.hpp"

namespace operation {

    class BitmapOperation : public Operation {

        // the input bitmap file
        bitmap::Bitmap _input;
        // the output bitmap file
        bitmap::Bitmap _output;

        public:

            BitmapOperation(std::string info, const bitmap::Bitmap& input, const bitmap::Bitmap& output);

            virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

            virtual void addOperationFileToCache() const override;
    };
}