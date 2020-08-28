#include "BitmapDIBHeader.hpp"
#include <string>
#include <cstdint>

namespace bitmap {

BitmapDIBHeader::BitmapDIBHeader(std::string data) 
    : BitAdjuster(std::move(data)), _bitmapWidth(bytesToInteger<uint32_t>(4)), _bitmapHeight(bytesToInteger<uint32_t>(8)),
    _bpp(bytesToInteger<uint16_t>(14)), _bmsize(bytesToInteger<uint32_t>(20)), _numcolors(bytesToInteger<uint32_t>(32)) {}

void BitmapDIBHeader::write() {
    std::string newData = getData().substr(0,4) + integerToBytes<uint32_t>(_bitmapWidth) + integerToBytes<uint32_t>(_bitmapHeight)
    + getData().substr(12, 2) + integerToBytes<uint16_t>(_bpp) + getData().substr(16, 4) + integerToBytes<uint32_t>(_bmsize)
    + getData().substr(24, 8) + integerToBytes<uint32_t>(_numcolors) + getData().substr(36);
    // setting the new data string
    setData(newData);
}

void BitmapDIBHeader::turn() {
    // swapping between the height and the width of the bitmap array
    uint32_t temp = _bitmapHeight;
    _bitmapHeight = _bitmapWidth;
    _bitmapWidth = temp;
}

void BitmapDIBHeader::gray() {}

uint16_t BitmapDIBHeader::getBitsPerPixel() {
    return _bpp;
}

uint32_t BitmapDIBHeader::getHeight() {
    return _bitmapHeight; 
}

uint32_t BitmapDIBHeader::getWidth() {
    return _bitmapWidth;
}

}
