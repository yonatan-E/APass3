#include "CrcHash.hpp"
#include "string"
#include "crc32.h"

namespace hash{

    CrcHash::CrcHash(const std::string input) : _input(input){}

    std::string CrcHash::applyAlgorithm(){
        return calculate_crc32c(0, (char*) _input, _input.size());
    }

    std::string CrcHash::getInput(){
        return _input;
    }
}