#include "ErrorCode.hpp"

namespace matrix {

    Exception::Exception(ErrorCode error) : std::runtime_error(error_getErrorMessage(error)) {}
}