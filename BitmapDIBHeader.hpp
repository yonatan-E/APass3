#pragma once

#include "BitAdjuster.hpp"
#include <string>


namespace bitmap {

/**
 * @brief This class represents the DIB Header of a BMP file. 
 * 
 */
class BitmapDIBHeader : public BitAdjuster {

    // size of header
    uint32_t _hsize = 40; 
    // width of bitmap
    uint32_t _bitmapWidth = 0;
    // height of bitmap
    uint32_t _bitmapHeight = 0; 
    // constant(always 1)
    uint16_t _con = 1; 
    // bits per pixel (8 or 24)
    uint16_t _bpp = 0; 
    // compression method (no compression, therfore 0)
    uint32_t _cm = 0; 
    // bitmap size;
    uint32_t _bmsize = 0; 
    // number of colors in color
    uint32_t _numcolors = 0; 

    public:

        /**
         * @brief Construct a new Bitmap DIB Header object
         * 
         * @param data the data string
         */
        explicit BitmapDIBHeader(std::string data);

        /**
         * @brief Construct a new Bitmap DIB Header object
         * 
         */
        BitmapDIBHeader() = default;

        /**
         * @brief The copy ctor
         * 
         * @param other the copied object
         */
        BitmapDIBHeader(const BitmapDIBHeader& other) = default;

        /**
         * @brief The copy assignment operator
         * 
         * @param other the copied object
         * @return BitmapDIBHeader& the current object
         */
        BitmapDIBHeader& operator=(const BitmapDIBHeader& other) = default;

        /**
         * @brief The move ctor
         * 
         * @param other the moved object
         */
        BitmapDIBHeader(BitmapDIBHeader&& other) noexcept = default;

        /**
         * @brief The move assignment operator
         * 
         * @param other the moved object
         * @return BitmapDIBHeader& the current object
         */
        BitmapDIBHeader& operator=(BitmapDIBHeader&& other) noexcept = default;

        /**
         * @brief Destroy the Bitmap DIB Header object
         * 
         */
        ~BitmapDIBHeader() = default;

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
         * @brief Get the number of the bits per pixel
         * 
         * @return uint16_t the bits per pixel
         */
        uint16_t getBitsPerPixel();

        /**
         * @brief Get the height of the bmp file
         * 
         * @return uint32_t the height 
         */
        uint32_t getHeight();

        /**
         * @brief Get the width of the bmp file
         * 
         * @return uint32_t the width 
         */
        uint32_t getWidth();
};

}