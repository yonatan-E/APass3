#pragma once

#include "BitAdjuster.hpp"
#include "ColorPallete.hpp"
#include "Matrix.hpp"
#include <string>

namespace bitmap {

/**
 * @brief This class represents the Bitmap Array of a BMP file.
 * 
 */
class BitmapArray : public BitAdjuster {
    // the color pallate
    ColorPallete _colors;
    // the pixels matrix
    matrix::Matrix _pixels;
    // the number of bits per pixel
    uint32_t _bitsPerPixel;
    // the height of the bitmap array
    uint32_t _height;
    // the width of the bitmap array
    uint32_t _width;

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
        explicit BitmapArray(std::string array_data, std::string color_data, uint32_t bpp, uint32_t height, uint32_t width);

        /**
         * @brief Construct a new Bitmap Array object
         * 
         */
        BitmapArray() = default;

        /**
         * @brief The copy constructor
         * 
         * @param other the copied object
         */
        BitmapArray(const BitmapArray& other) = default;
        
        /**
         * @brief The copy assignment operator
         * 
         * @param other the copied object
         * @return BitmapArray& the current object
         */
        BitmapArray& operator=(const BitmapArray& other) = default;

        /**
         * @brief The move constructor
         * 
         * @param other the moved object
         */
        BitmapArray(BitmapArray&& other) noexcept = default;

        /**
         * @brief The move assignment operator
         * 
         * @param other the moved object
         * @return BitmapArray& the current object
         */
        BitmapArray& operator=(BitmapArray&& other) noexcept = default;

        /**
         * @brief Destroy the Bitmap Array object
         * 
         */
        ~BitmapArray() = default;

        /**
         * @brief Method that writes the content of the object into the string
         * 
         */
        virtual void write() override;

        /**
         * @brief Method that changes the content of the current object according to the turn
         * 
         */
        virtual void turn() override;

        /**
         * @brief Method that changes the content of the current object according to the
                  color changing to gray
         * 
         */
        virtual void gray() override;

        /**
         * @brief Get the Color Pallete of the object
         * 
         * @return const ColorPallete& the color pallete
         */
        const ColorPallete& getColorPallete();
};

}