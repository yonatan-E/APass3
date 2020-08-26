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
    uint16_t _fileType = 0x4D42; 
    // file size in bytes
    uint32_t _fileSize = 0;
    // reserved 
    uint16_t _reserved1 = 0;
    uint16_t _reserved2 = 0;
    // offset
    uint32_t _offset = 0;

    public:

        /**
         * @brief Construct a new Bitmap Header object
         * 
         * @param data the given data string
         */
        explicit BitmapHeader(std::string data);

        /**
         * @brief Construct a new Bitmap Header object
         * 
         */
        BitmapHeader() = default;

        /**
         * @brief The copy ctor
         * 
         * @param other the copied object
         */
        BitmapHeader(const BitmapHeader& other) = default;
        
        /**
         * @brief The copy assignment operator
         * 
         * @param other the copied object
         * @return BitmapHeader& the current object
         */
        BitmapHeader& operator=(const BitmapHeader& other) = default;

        /**
         * @brief The move ctor
         * 
         * @param other the moved object
         */
        BitmapHeader(BitmapHeader&& other) noexcept = default;

        /**
         * @brief The move assignment operator
         * 
         * @param other the moved object
         * @return BitmapHeader& the current object
         */
        BitmapHeader& operator=(BitmapHeader&& other) noexcept = default;

        /**
         * @brief Destroy the Bitmap Header object
         * 
         */
        ~BitmapHeader() = default;

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
         * @brief Get the bitmap array Offset 
         * 
         * @return uint32_t the offset of the bitmap array
         */
        uint32_t getOffset();
};

}