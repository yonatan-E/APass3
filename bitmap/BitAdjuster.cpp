#include "BitAdjuster.hpp"
#include <string>
#include <cstring>
#include <iostream>

namespace bitmap {

    BitAdjuster::BitAdjuster(std::string data) : _data(std::move(data)) {}

    const std::string& BitAdjuster::getData() const {
        return this->_data;
    }

    void BitAdjuster::setData(std::string data) {
        this->_data = std::move(data);
    }

}