#include "CacheManager.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <algorithm>
#include <iterator>

namespace cache {

    CacheManager::CacheManager(uint32_t maxSize, std::string pathToInfoFile)
    : _maxSize(maxSize), _pathToInfoFile(std::move(pathToInfoFile)) {
        
        std::ifstream info(_pathToInfoFile);

        if (!info.is_open()) {
            std::ofstream temp(_pathToInfoFile);
            temp.close();
        }

        std::copy(std::istream_iterator<uint32_t>(info), std::istream_iterator<uint32_t>(), std::back_inserter(_hashCodes));

        info.close();
    }

    bool CacheManager::contains(uint32_t hashCode) const {
        return std::find(_hashCodes.begin(), _hashCodes.end(), hashCode) != _hashCodes.end();
    }

    void CacheManager::load(const operation::Operation& operation) {

        if (!contains(operation.getHashCode())) {

            if (_hashCodes.size() >= _maxSize) {

                if (remove(("cache/" + std::to_string(*(_hashCodes.begin())) + ".txt").c_str()) != 0) {
                    throw operation::exceptions::FileDeleteException();
                }

                _hashCodes.erase(_hashCodes.begin());
            }

            _hashCodes.push_back(operation.getHashCode());

        } else {
            _hashCodes.erase(std::find(_hashCodes.begin(), _hashCodes.end(), operation.getHashCode()));
            _hashCodes.push_back(operation.getHashCode());
        }

        std::ofstream info(_pathToInfoFile, std::ios::trunc);

        if (!info.is_open()) {
            throw operation::exceptions::FileOpenException();
        }

        std::for_each(_hashCodes.begin(), _hashCodes.end(), [&info](uint32_t hash) {
            info << hash << '\n';
        });

        operation.addOperationFileToCache();
    }
}