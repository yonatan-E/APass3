#include "Operation.hpp"
#include "OperationExceptions.hpp"
#include <string>
#include <cstdio>

namespace operation {

    Operation::Operation() {
            // current date/time based on current system
            time_t now = time(0);
            // initializing the info string with current date/time
            _info = std::move(ctime(&now)); 
            // initializing the path to the file in the cache
            _cachePath = std::move("cache/" + std::string(_info).replace(_info.find(" "), sizeof(_info), "_"));
        }

    void Operation::deleteOperationFileFromCache() const {
        if (remove(_cachePath.c_str()) != 0) {
            throw exceptions::FileDeleteException();
        } 
    }

    const std::string& Operation::getInfo() const {
        return _info;
    }

    const std::string& Operation::getCachePath() const {
        return _cachePath;
    }
}