#include "BitmapOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>

namespace operation {

    BitmapOperation::BitmapOperation(uint32_t hashCode, const bitmap::Bitmap& result)
        : Operation(hashCode),
        _result(result) {}

    void BitmapOperation::writeOperationToFile(const std::string& filePath) const {
        // writing the result object to the output file
        try {
            _result.writeToFile(filePath);
        } catch (...) {
            throw exceptions::FileWriteException();
        }
    }
}
