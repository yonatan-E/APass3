#pragma once
#include "string"

namespace hash{

    class CrcHash{

        std::string _input;

        public:

            CrcHash(const std::string input);

            std::string applyAlgorithm();

            std::string getInput();

    };
}