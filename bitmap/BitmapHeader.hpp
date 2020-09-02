#pragma once
#include "BitAdjuster.hpp"
#include <string>

namespace bitmap {

/**
 * @brief This class represents the Header of a BMP file.
 * 
 */
class BitmapHeader : public BitAdjuster {
    
    // the file type, which is always 0x4D42
    const uint16_t m_fileType = 0x4D42; 
    // file size in bytes
    const uint32_t m_fileSize;
    // reserved 
    const uint16_t m_reserved1;
    const uint16_t m_reserved2;
    // offset
    const uint32_t m_offset;

    public:

        /**
         * @brief Construct a new Bitmap Header object
         * 
         * @param data the given data string
         */
        BitmapHeader(std::string data);

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
         * @brief Get the bitmap array Offset 
         * 
         * @return uint32_t the offset of the bitmap array
         */
        uint32_t getOffset() const;
};

}