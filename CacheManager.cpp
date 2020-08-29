#include "CacheManager.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <algorithm>

namespace cache {

    CacheManager::CacheManager(uint32_t maxSize, std::string pathToInfoFile)
    : _hashCodes(maxSize), _pathToInfoFile(std::move(pathToInfoFile)) {
        
        std::ifstream info(_pathToInfoFile);

        if (!info.is_open()) {
            throw operation::exceptions::FileOpenException();
        }

        char* line;
        while (info.getline(line, sizeof(uint32_t), '\n')) {
            try {
                _hashCodes.push_back(std::stoi(line));
            } catch (...) {
                throw operation::exceptions::FileFormatException();
            } 
        }

        info.close();
    }

    bool CacheManager::contains(const operation::Operation& operation) {
        return std::find(_hashCodes.begin(), _hashCodes.end(), operation.getHashCode()) != _hashCodes.end();
    }

    void CacheManager::add(const operation::Operation& operation) {
        if (!contains(operation)) {
            _hashCodes.push_back(operation.getHashCode());
            
            if (_hashCodes.size() >= _hashCodes.max_size()) {
                _hashCodes.erase(_hashCodes.begin());
            }

            _hashCodes.push_back(operation.getHashCode());

        } else {
            std::vector<uint32_t>::iterator current = 
                std::find(_hashCodes.begin(), _hashCodes.end(), operation.getHashCode());
            _hashCodes.erase(current);
            _hashCodes.push_back(*current);
        }

        std::ofstream info(_pathToInfoFile, std::ios::trunc);

        if (!info.is_open()) {
            throw operation::exceptions::FileOpenException();
        }

        std::for_each(_hashCodes.begin(), _hashCodes.end(), [&info](std::vector<uint32_t>::iterator it) {
            info << *it << '\n';
        });
    }
}