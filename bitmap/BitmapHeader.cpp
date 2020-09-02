#include "BitmapHeader.hpp"
#include <string>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace bitmap {

BitmapHeader::BitmapHeader(std::string data) 
    : BitAdjuster(std::move(data)), m_fileSize(bytesToInteger<uint32_t>(2)), m_reserved1(bytesToInteger<uint16_t>(6)),
    m_reserved2(bytesToInteger<uint16_t>(8)), m_offset(bytesToInteger<uint32_t>(10)) {
        // a file in BMP format must start with 0x4D42
        if (bytesToInteger<uint16_t>(0) != 0x4D42) {
            throw std::runtime_error("The file is not in the correct BMP format");
        }
    }

void BitmapHeader::write() {}

void BitmapHeader::turn() {}

void BitmapHeader::gray() {}

uint32_t BitmapHeader::getOffset() const {
    return m_offset;
}

}