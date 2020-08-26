#include "BitmapOperation.hpp"
#include "OperationExceptions.hpp"
#include <stdexcept>
#include <fstream>

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

        // writing the data string of the output bitmap file into the cache file
		cacheFile.write(_output.getData().data(), static_cast<std::streamsize>(_output.getData().length()));
        // checking if an error has occured while writing to the file
		if (!cacheFile) {
            cacheFile.close();
			throw exceptions::FileWriteException();
		}

        // closing the ofstream
        cacheFile.close();
    }
}
