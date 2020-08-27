#include "BitmapOperation.hpp"
#include "OperationExceptions.hpp"
#include <stdexcept>
#include <fstream>

namespace operation {

    BitmapOperation::BitmapOperation(const bitmap::Bitmap& input, OperationType type)
        :_input(input),
        _type(type) {} 

    void BitmapOperation::writeOperationToOutputFile(const std::string& outputPath) const {
        // creating a copy of the input object to not affect him with turn() or gray()
        bitmap::Bitmap result(_input);

        // doing the operation on the copy to get the correct result object
        if (_type == OperationType::rotate) {
            result.turn();
        } else {
            result.gray();
        }

        // writing the result object to the output file
        try {
            result.writeToFile(outputPath);
        } catch (...) {
            throw exceptions::FileWriteException();
        }
    }

    void BitmapOperation::addOperationFileToCache() const {
        // opening the cache file using ofstream
		std::ofstream cacheFile(getCachePath(), std::ios::binary | std::ios::trunc);
        
        // checking if an error has occured while opening the file
		if (!cacheFile.is_open()) {
			throw exceptions::FileOpenException();
		}

		// writing the data string of the input bitmap file into the cache file
		cacheFile.write(_input.getData().data(), static_cast<std::streamsize>(_input.getData().length()));
        // checking if an error has occured while writing to the file
		if (!cacheFile) {
            cacheFile.close();
			throw exceptions::FileWriteException();
		}

        // line seperator
        cacheFile << '\n';

        // writing the operation type into the cache file
        if (_type == OperationType::rotate) {
            cacheFile << "rotate";
        } else {
            cacheFile << "convert";
        }

        // closing the ofstream
        cacheFile.close();
    }
}
