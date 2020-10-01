#include "BitmapOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>

namespace operation {

    BitmapOperation::BitmapOperation(const uint32_t hashCode, const bitmap::Bitmap& result)
        : Operation(hashCode),
        m_result(result) {}

    void BitmapOperation::writeOperationToFile(const std::string& filePath) const {
        try {
            m_result.writeToFile(filePath);
        } catch (...) {
            // catching the exception which was thrown at the writeToFile() method,
            // and converting it to FileWriteException.
            throw exceptions::FileWriteException();
        }
    }
}
