#include "Operation.hpp"
#include "OperationExceptions.hpp"
#include <string>
#include <cstdio>

namespace operation {

    Operation::Operation(uint32_t hashCode) : _hashCode(hashCode) {
            // current date/time based on current system
            time_t now = time(0);
            // initializing the info string with current date/time
            _info = std::move(ctime(&now)); 
        }

    void Operation::deleteOperationFileFromCache() const {
        if (remove("cache/" + _hashCode) != 0) {
            throw exceptions::FileDeleteException();
        } 
    }

    uint32_t Operation::getHashCode() const {
        return _hashCode;
    }

    const std::string& Operation::getInfo() const {
        return _info;
    }
}