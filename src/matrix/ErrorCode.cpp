#include "ErrorCode.hpp"

namespace matrix {

    Exception::Exception(const ErrorCode error) : std::runtime_error(error_getErrorMessage(error)) {}
}