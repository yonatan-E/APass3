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
        _type == OperationType::rotate ? result.turn() : result.gray();

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

        // writing the operation type into the cache file
        _type == OperationType::rotate ? cacheFile << '\n' << "rotate" << '\n' : cacheFile << '\n' << "convert" << '\n';

        // getting the result bitmap
        // creating a copy of the input object to not affect him with turn() or gray()
        bitmap::Bitmap result(_input);
        // doing the operation on the copy to get the correct result object
        _type == OperationType::rotate ? result.turn() : result.gray();

        // writing the data string of the result bitmap file into the cache file
		cacheFile.write(_input.getData().data(), static_cast<std::streamsize>(_input.getData().length()));
        // checking if an error has occured while writing to the file
		if (!cacheFile) {
            cacheFile.close();
			throw exceptions::FileWriteException();
		}

        // closing the ofstream
        cacheFile.close();
    }

    bool BitmapOperation::operator==(const Operation& other) const {
        try {
            const BitmapOperation& otherBitmap = dynamic_cast<const BitmapOperation&>(other);
            return this->_input == otherBitmap._input
            && this->_type == otherBitmap._type;
        } catch (...) {
            return false;
        }
    }
}
