#pragma once

#include "BitAdjuster.hpp"
#include "BitmapHeader.hpp"
#include "BitmapDIBHeader.hpp"
#include "ColorPallete.hpp"
#include "BitmapArray.hpp"
#include <string>

namespace bitmap {

/**
 * @brief This class represents a BMP file.
 * 
 */
class Bitmap: public BitAdjuster {
    
    // the header of the bitmap file
    BitmapHeader _header;
    // the DIB header of the bitmap file
    BitmapDIBHeader _dibHeader;
    // the bitmap array
    BitmapArray _bitmapArray;

    public:

        /**
         * @brief Construct a new Bitmap object
         * 
         * @param inputPath the path to the input file
         */
        explicit Bitmap(const std::string& inputPath);

        /**
         * @brief The copy constructor
         * 
         * @param other the copied object
         */
        Bitmap(const Bitmap& other) = default;

        /**
         * @brief The copy assignment operator
         * 
         * @param other the copied object
         * @return Bitmap& the current object
         */
        Bitmap& operator=(const Bitmap& other) = default;
 
        /**
         * @brief The move constructor
         * 
         * @param other the moved object
         */
        Bitmap(Bitmap&& other) noexcept = default;

        /**
         * @brief The move assignment operator
         * 
         * @param other the moved object
         * @return Bitmap& the current object
         */
        Bitmap& operator=(Bitmap&& other) noexcept = default;

        /**
         * @brief Destroy the Bitmap object
         * 
         */
        ~Bitmap() = default;

        /**
         * @brief The bitmap compare operator
         * 
         * @param other the bitmap which the current bitmap is compared to
         * @return true if the bitmaps are equal
         * @return false if the bitmaps aren't equal
         */
        bool operator==(const Bitmap& other) const;

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
         * @brief write the data string to an output file
         * 
         * @param outputPath the path to the output file
         */
        void writeToFile(const std::string& outputPath) const;

    private:
        
        /**
         * @brief Read the content of a file
         * 
         * @param path the path to the file
         * @return std::string the content of the file
         */
        static std::string readFileContent(const std::string& path);
};

}