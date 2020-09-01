#include "Operation.hpp"
#include "../exceptions/OperationExceptions.hpp"
#include <string>
#include <cstdio>

namespace operation {

    Operation::Operation(uint32_t hashCode) : _hashCode(hashCode) {}

    uint32_t Operation::getHashCode() const {
        return _hashCode;
    }
}