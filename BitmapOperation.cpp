#include "BitmapOperation.hpp"
#include "OperationExceptions.hpp"
#include <stdexcept>

namespace operation {

    BitmapOperation::BitmapOperation(std::string info, const bitmap::Bitmap& input, const bitmap::Bitmap& output)
        : Operation(info),
        _input(input),
        _output(output) {} 

    void BitmapOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        try {
            _output.writeToFile(outputPath);
        } catch (...) {
            throw exceptions::FileWriteException();
        }
    }

    void BitmapOperation::addOperationFileToCache() const {
        
    }
}
