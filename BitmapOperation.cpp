#include "BitmapOperation.hpp"
#include "OperationExceptions.hpp"

namespace operation {

    BitmapOperation::BitmapOperation(std::string info, const bitmap::Bitmap& input, const bitmap::Bitmap& output)
        : Operation(info),
        _input(input),
        _output(output) {} 
}
