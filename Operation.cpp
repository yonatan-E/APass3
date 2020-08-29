#include "Operation.hpp"
#include "OperationExceptions.hpp"
#include <string>
#include <cstdio>

namespace operation {

    Operation::Operation(uint32_t hashCode) : _hashCode(hashCode) {}

    void Operation::deleteOperationFileFromCache() const {
        if (remove("cache/" + _hashCode) != 0) {
            throw exceptions::FileDeleteException();
        } 
    }

    uint32_t Operation::getHashCode() const {
        return _hashCode;
    }
}