#pragma once

#include <string>

namespace hash {

    class CrcHash {

        std::string _input;

        public:

            CrcHash(std::string input);

            std::string applyAlgorithm() const;

            const std::string& getInput() const;
    };
}