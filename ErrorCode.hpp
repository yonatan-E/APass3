#pragma once

#include "ErrorCode.h"
#include <stdexcept>

namespace matrix {
    
    /**
     * @brief This class defines an exception which is defined by an error code
     */
    class Exception : public std::runtime_error {
        
        public:
        
            /**
             * @brief The constructor, that creates a new exception by an error code
             * 
             * @param error the given error code
             */
            Exception(ErrorCode error);
    };
}