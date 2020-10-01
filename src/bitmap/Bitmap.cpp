#include "Bitmap.hpp"
#include <fstream>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace bitmap {

    Bitmap::Bitmap(const std::string& inputPath) 
        : BitAdjuster(std::move(readFileContent(inputPath))),
        m_header(getData().substr(0,14)), m_dibHeader(getData().substr(14,40)), 
        m_bitmapArray(getData().substr(m_header.getOffset()), getData().substr(54 , m_header.getOffset() - 54),
        m_dibHeader.getBitsPerPixel(), m_dibHeader.getHeight(), m_dibHeader.getWidth()) {}

    void Bitmap::write() {
        // activing write() for all of the parts of the bitmap
        m_header.write();
        m_dibHeader.write();
        m_bitmapArray.write();
        
        // setting the new data string to be the data string of the bitmap
        setData(m_header.getData() + m_dibHeader.getData()
        + m_bitmapArray.getColorPallete().getData() + m_bitmapArray.getData());
    }

    void Bitmap::turn() {
        // activing turn() for all of the parts of the bitmap
        m_header.turn();
        m_dibHeader.turn();
        m_bitmapArray.turn();

        // writing the changes into the data string
        write();
    }

    void Bitmap::gray() {
        // activing gray() for bitmap array, because it is the only part
        // which is affected by the color changing to gray
        m_bitmapArray.gray();

        // writing the changes into the data string
        write();
    }

	void Bitmap::writeToFile(const std::string& outputPath) const {
		// opening the file
		std::ofstream out(outputPath, std::ios::binary | std::ios::trunc);

		// checking if an error has occured while opening the file
		if (!out) {
			throw std::runtime_error("An error has occured while opening the file");
		}

		// writing the data string to the file
		out.write(getData().data(), static_cast<std::streamsize>(getData().length()));

		// checking if an error has occured while writing to the file
		if (!out) {
			throw std::runtime_error("An error has occured while writing to the file");
		}
	}

    std::string Bitmap::readFileContent(const std::string& filePath) { 
        // opening the file
        std::ifstream in(filePath, std::ios::binary);

        // checking if an error has occured while opening the file
        if (!in) {
            throw std::runtime_error("An error has occured while opening the file");
        }

        // reading the content from the file
        auto content = std::string{std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};

        // checking if an error has occured while reading from the file
        if (!in) {
            throw std::runtime_error("An error has occured while reading from the file");
        }

        return content;
    }

}