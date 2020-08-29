#pragma once

#include <string>

namespace hash {

    class CrcHash {

        std::string _input;

        public:

            CrcHash(std::string input);

            bool operator==(const CrcHash& other) const;

            std::string applyAlgorithm() const;

            const std::string& getInput() const;
    };
}