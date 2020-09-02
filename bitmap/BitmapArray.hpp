#pragma once

#include "BitAdjuster.hpp"
#include "ColorPallete.hpp"
#include "Matrix.hpp"
#include <string>
#include <array>
#include <cstdint>

namespace bitmap {

/**
 * @brief This class represents the Bitmap Array of a BMP file.
 * 
 */
class BitmapArray : public BitAdjuster {
    // the color pallate
    ColorPallete m_colors;
    // the pixels matrix
    matrix::Matrix m_pixels;
    // the number of bits per pixel
    const uint32_t m_bitsPerPixel;
    // the height of the bitmap array
    uint32_t m_height;
    // the width of the bitmap array
    uint32_t m_width;

    public:

        /**
         * @brief Construct a new Bitmap Array object
         * 
         * @param array_data the data string of the bitmap array
         * @param color_data the data string of the color pallete
         * @param bpp the number of bits per pixel
         * @param height the height of the bmp file
         * @param width the width of the bmp file
         */
        BitmapArray(std::string array_data, std::string color_data, const uint32_t bpp, const uint32_t height, const uint32_t width);

        /**
         * @brief Method that writes the content of the object into the string
         * 
         */
        void write() override;

        /**
         * @brief Method that changes the content of the current object according to the turn
         * 
         */
        void turn() override;

        /**
         * @brief Method that changes the content of the current object according to the
                  color changing to gray
         * 
         */
        void gray() override;

        /**
         * @brief Get the Color Pallete of the object
         * 
         * @return const ColorPallete& the color pallete
         */
        const ColorPallete& getColorPallete() const;
};

}