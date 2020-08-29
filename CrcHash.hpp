#pragma once

#include <string>
#include <cstdint>

namespace hash {

    class CrcHash {

        std::string _input;

        public:

            CrcHash(std::string input);

            uint32_t applyAlgorithm() const;

            const std::string& getInput() const;
    };
}