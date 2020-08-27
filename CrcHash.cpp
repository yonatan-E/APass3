#include "CrcHash.hpp"
#include "crc32.h"
#include <string>

namespace hash {

    CrcHash::CrcHash(std::string input) : _input(std::move(input)) {}

    std::string CrcHash::applyAlgorithm() const {
        return std::move(calculate_crc32c(0, (char*) _input, _input.size()));
    }

    const std::string& CrcHash::getInput() const {
        return _input;
    }
}