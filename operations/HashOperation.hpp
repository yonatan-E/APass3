#pragma once

#include "Operation.hpp"
#include "CrcHash.hpp"

namespace operation {

    /**
     * @brief This class represents a hash operation, which has a result and a hashCode.
            A hash operation can be only apply the crc32 algorithm on a string.
     * 
     */
    class HashOperation : public Operation {
        
        public:

            /**
             * @brief Construct a new Hash Operation object
             * 
             * @param hashCode the hashCode of the operation
             * @param result the result hashCode of the operation
             */
            HashOperation(const uint32_t hashCode, const uint32_t result);

            /**
             * @brief Write the result of the operation to a file
             * 
             * @param filePath the file path
             */
            virtual void writeOperationToFile(const std::string& filePath) const override;

        private:

            // the result hashCode of the operation (crc32 algorithm)
            const uint32_t m_result;
    };
}