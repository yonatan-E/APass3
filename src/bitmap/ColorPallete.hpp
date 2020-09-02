#pragma once

#include "BitAdjuster.hpp"
#include <string>
#include <vector>
#include <array>

namespace bitmap {

/**
 * @brief This class represents the Color Pallete of a BMP file.
 * 
 */
class ColorPallete : public BitAdjuster {
    
    // a vector with all of the colors
    std::vector<std::array<int, 3>> m_colors; 

    public:

        /**
         * @brief Construct a new Color Pallete object
         * 
         * @param data the given data string
         */
        ColorPallete(std::string data);

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
         * @brief Method that adds the given color to the color pallete
         * 
         * @param b the blue rank of the color
         * @param g the green rank of the color
         * @param r the red rank of the colot
         */
        void addColor(int b, int g, int r);

        /**
         * @brief Get the Color object
         * 
         * @param index the given index
         * @return std::array<int, 3> the color in the given index
         */
        std::array<int, 3> getColor(uint32_t index) const;
};

}