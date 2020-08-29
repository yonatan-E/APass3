#include "BitmapOperation.hpp"
#include "OperationExceptions.hpp"
#include <fstream>

namespace operation {

    BitmapOperation::BitmapOperation(uint32_t hashCode, const bitmap::Bitmap& result)
        : Operation(hashCode),
        _result(result) {}

    void BitmapOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        // writing the result object to the output file
        try {
            _result.writeToFile(outputPath);
        } catch (...) {
            throw exceptions::FileWriteException();
        }
    }

    void BitmapOperation::addOperationFileToCache() const {
        // opening the cache file using ofstream
		std::ofstream cacheFile("cache/" + getHashCode(), std::ios::binary | std::ios::trunc);
        
        // checking if an error has occured while opening the file
		if (!cacheFile.is_open()) {
			throw exceptions::FileOpenException();
		}

        // writing the data string of the result bitmap file into the cache file
		cacheFile.write(_result.getData().data(), static_cast<std::streamsize>(_result.getData().length()));
        // checking if an error has occured while writing to the file
		if (!cacheFile) {
            cacheFile.close();
			throw exceptions::FileWriteException();
		}

        // closing the ofstream
        cacheFile.close();
    }
}
