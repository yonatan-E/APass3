#include "CrcHash.hpp"
#include"string"

namespace hash{

    CrcHash::CrcHash(const std::string input) : _input(input){}

    std::string CrcHash::applyAlgorithm(){

    }

    std::string CrcHash::getInput(){
        return _input;
    }
}