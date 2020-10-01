#include "CrcHash.hpp"
#include "crc32.h"
#include <string>

namespace hash {

    CrcHash::CrcHash(std::string input) : m_input(std::move(input)) {}

    uint32_t CrcHash::applyAlgorithm() const {
        return calculate_crc32c(0, reinterpret_cast<const unsigned char*>(m_input.c_str()), m_input.size());
    }

    const std::string& CrcHash::getInput() const {
        return m_input;
    }
}