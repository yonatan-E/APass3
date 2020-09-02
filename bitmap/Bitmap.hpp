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
    BitmapHeader m_header;
    // the DIB header of the bitmap file
    BitmapDIBHeader m_dibHeader;
    // the bitmap array
    BitmapArray m_bitmapArray;

    public:

        /**
         * @brief Construct a new Bitmap object
         * 
         * @param inputPath the path to the input file
         */
        Bitmap(const std::string& inputPath);

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