#include "Operation.hpp"
#include "OperationExceptions.hpp"
#include <string>
#include <cstdio>

namespace operation {

    Operation::Operation(std::string info) 
        : _info(std::move(info)), _cachePath(std::move(std::string(_info).replace(_info.find(" "), sizeof(_info), "_"))) {}

    void Operation::deleteOperationFileFromCache() const {
        if (remove(_cachePath.c_str()) != 0) {
            throw exceptions::FileDeleteException();
        } 
    }

    const std::string& Operation::getCachePath() const {
        return _cachePath;
    }
}