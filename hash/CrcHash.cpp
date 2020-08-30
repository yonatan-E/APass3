#include "CrcHash.hpp"
#include "crc32.h"
#include <string>

namespace hash {

    CrcHash::CrcHash(std::string input) : _input(std::move(input)) {}

    uint32_t CrcHash::applyAlgorithm() const {
        return calculate_crc32c(0, (const unsigned char*)_input.c_str(), _input.size());
    }

    const std::string& CrcHash::getInput() const {
        return _input;
    }
}