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
    uint32_t m_hsize = 40; 
    // width of bitmap
    uint32_t m_bitmapWidth = 0;
    // height of bitmap
    uint32_t m_bitmapHeight = 0; 
    // constant(always 1)
    uint16_t m_con = 1; 
    // bits per pixel (8 or 24)
    uint16_t m_bpp = 0; 
    // compression method (no compression, therfore 0)
    uint32_t m_cm = 0; 
    // bitmap size;
    uint32_t m_bmsize = 0; 
    // number of colors in color
    uint32_t m_numcolors = 0; 

    public:

        /**
         * @brief Construct a new Bitmap DIB Header object
         * 
         * @param data the data string
         */
        BitmapDIBHeader(std::string data);

        /**
         * @brief Construct a new Bitmap DIB Header object
         * 
         */
        BitmapDIBHeader() = default;

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
        uint16_t getBitsPerPixel() const;

        /**
         * @brief Get the height of the bmp file
         * 
         * @return uint32_t the height 
         */
        uint32_t getHeight() const;

        /**
         * @brief Get the width of the bmp file
         * 
         * @return uint32_t the width 
         */
        uint32_t getWidth() const;
};

}