#include "BitmapArray.hpp"
#include <string>
#include <utility>
#include <cstdint>

namespace bitmap {

BitmapArray::BitmapArray(std::string array_data, std::string color_data, const uint32_t bpp, const uint32_t height, const uint32_t width) 
        : BitAdjuster(std::move(array_data)), m_colors(std::move(color_data)), m_pixels(height, width),
        m_bitsPerPixel(bpp), m_height(height), m_width(width) {
    // initializing the matrix and the collor pallete, according to the specific case:
    // in case that pixel size is 8 bit 
    if (m_bitsPerPixel == 8) {
        // iterating over the data string and itializing the matrix
        uint32_t index = 0;
        for (uint32_t i = 0; i < m_height ; i++) {
            for (uint32_t j = 0; j < m_width ; j++) {
                m_pixels.setAt(i, j, bytesToInteger<uint8_t>(index));
                index++;
            }
        }   
    }

    // in case that pixel size is 24 bit
    if (m_bitsPerPixel == 24) {
        uint32_t index = 0, runner = 0; 
        // iterating over the data string and initializing the color pallete and the matrix
        for (uint32_t i = 0; i < m_height; i++) {
            for (uint32_t j = 0; j < m_width; j++) {
                // adding the current index to the exact place in the matrix
                m_pixels.setAt(i, j, index);
                // adding the color to the color pallete
                m_colors.addColor(bytesToInteger<uint8_t>(runner),bytesToInteger<uint8_t>(runner + 1),
                bytesToInteger<uint8_t>(runner + 2));
                runner += 3;
                index++;
            }
        }  
    }
}

void BitmapArray::write() {
    // initializing the data string with a new data string,
    // according to the specific case:
    // in case that pixel size is 8 bit
    if (m_bitsPerPixel == 8) {
        // activing the write() function for the color pallete
        m_colors.write();
        // iterating over the matrix and adding the indexes of all of the pixels to the data string
        for (uint32_t i = 0; i < m_height ; i++) {
            for (uint32_t j = 0; j < m_width ; j++) {
                setData(getData().substr(0, j + i * m_width) + integerToBytes<uint8_t>(m_pixels(i, j))
                + getData().substr(j + i * m_width + 1));
            }
        }   
    }

    // in case that pixel size is 24 bit
    if (m_bitsPerPixel == 24) {
        std::string newData = "";
        // iterating over the matrix and adding the colors of all of the pixels to the data string
        for (uint32_t i = 0; i < m_height; i++) {
            for (uint32_t j = 0; j < m_width; j++) {
                newData += integerToBytes<uint8_t>(m_colors.getColor(m_pixels(i, j))[0]) 
                + integerToBytes<uint8_t>(m_colors.getColor(m_pixels(i, j))[1]) 
                + integerToBytes<uint8_t>(m_colors.getColor(m_pixels(i, j))[2]);
            }
            // for padding
            for (uint32_t k = 0; k < m_width % 4; k++) {
                newData += integerToBytes<uint8_t>(0x00); 
            }   
        }
        // setting the new data
        setData(newData); 
    }
}

void BitmapArray::turn() {
    // swapping between the height and the width of the bitmap array
    uint32_t temp = m_height;
    m_height = m_width;
    m_width = temp;

    // turning the matrix
    m_pixels.turn();
}

void BitmapArray::gray() {
    // activing gray() for the color pallete
    m_colors.gray();
}

const ColorPallete& BitmapArray::getColorPallete() const {
    return m_colors;
}

}

