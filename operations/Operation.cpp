#include "Operation.hpp"
#include "OperationExceptions.hpp"
#include <string>
#include <cstdio>

namespace operation {

    Operation::Operation(uint32_t hashCode) : m_hashCode(hashCode) {}

    uint32_t Operation::getHashCode() const {
        return m_hashCode;
    }
}