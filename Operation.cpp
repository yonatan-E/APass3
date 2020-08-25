#include "Operation.hpp"
#include <cstdio>

namespace operation {

    void Operation::deleteOperationFileFromCache() const {
        if (remove(_cachePath.c_str()) != 0) {
            throw FileDeleteException();
        } 
    }

    const std::string& Operation::getCachePath() const {
        return _cachePath;
    }
}