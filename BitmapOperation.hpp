#pragma once

#include "Operation.hpp"
#include "Bitmap.hpp"

namespace operation {

    /**
     * @brief This class represents a bitmap operation, which has a result and a hashCode.
            A bitmap operation can be rotate or convert a bitmap file.
     * 
     */
    class BitmapOperation : public Operation {

        public:

            /**
             * @brief Construct a new Bitmap Operation object
             * 
             * @param hashCode the hashCode of the operation
             * @param result the result bitmap of the operation
             */
            BitmapOperation(uint32_t hashCode, const bitmap::Bitmap& result);

            /**
             * @brief Write the result of the operation to a file
             * 
             * @param filePath 
             */
            virtual void writeOperationToFile(const std::string& filePath) const override;

        private:

            // the result bitmap of the operation (rotate or convert to grayscale)
            bitmap::Bitmap _result;
    };
}