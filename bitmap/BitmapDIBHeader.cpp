#include "BitmapDIBHeader.hpp"
#include <string>
#include <cstdint>

namespace bitmap {

BitmapDIBHeader::BitmapDIBHeader(std::string data) 
    : BitAdjuster(std::move(data)), m_bitmapWidth(bytesToInteger<uint32_t>(4)), m_bitmapHeight(bytesToInteger<uint32_t>(8)),
    m_bpp(bytesToInteger<uint16_t>(14)), m_bmsize(bytesToInteger<uint32_t>(20)), m_numcolors(bytesToInteger<uint32_t>(32)) {}

void BitmapDIBHeader::write() {
    std::string newData = getData().substr(0,4) + integerToBytes<uint32_t>(m_bitmapWidth) + integerToBytes<uint32_t>(m_bitmapHeight)
    + getData().substr(12, 2) + integerToBytes<uint16_t>(m_bpp) + getData().substr(16, 4) + integerToBytes<uint32_t>(m_bmsize)
    + getData().substr(24, 8) + integerToBytes<uint32_t>(m_numcolors) + getData().substr(36);
    // setting the new data string
    setData(newData);
}

void BitmapDIBHeader::turn() {
    // swapping between the height and the width of the bitmap array
    uint32_t temp = m_bitmapHeight;
    m_bitmapHeight = m_bitmapWidth;
    m_bitmapWidth = temp;
}

void BitmapDIBHeader::gray() {}

uint16_t BitmapDIBHeader::getBitsPerPixel() const {
    return m_bpp;
}

uint32_t BitmapDIBHeader::getHeight() const {
    return m_bitmapHeight; 
}

uint32_t BitmapDIBHeader::getWidth() const {
    return m_bitmapWidth;
}

}
