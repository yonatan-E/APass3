#include "CacheManager.hpp"
#include "OperationExceptions.hpp"
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sys/stat.h>

namespace cache {

    CacheManager::CacheManager(uint32_t maxSize, std::string directoryPath)
    : _maxSize(maxSize), _directoryPath(std::move(directoryPath)) {
        
        // checking if the directory exists
        struct stat buffer;
        if (stat(_directoryPath.c_str(), &buffer) != 0) {
            // if the directory doesn't exist, creating a new one
            if (mkdir(_directoryPath.c_str(), 0777) != 0) {
                throw operation::exceptions::FileOpenException();
            }
        }

        // opening the info file using ifstream
        std::ifstream info(_directoryPath + "/info.txt");

        // if the file isn't exist, creating the file using ofstream
        if (!info.is_open()) {
            std::ofstream creator(_directoryPath + "/info.txt");
            creator.close();
        }

        // reading the content of the info file into the vector
        std::copy(std::istream_iterator<uint32_t>(info), std::istream_iterator<uint32_t>(), std::back_inserter(_hashCodes));

        // closing the ifstream
        info.close();
    }

    bool CacheManager::contains(uint32_t hashCode) const {
        // trying to find the hash code in the vector
        return std::find(_hashCodes.begin(), _hashCodes.end(), hashCode) != _hashCodes.end();
    }

    void CacheManager::load(const operation::Operation& operation) {
        // if the cache doesn't contain the hash code of the operation, adding the operation to the cache
        if (!contains(operation.getHashCode())) {

            // if the cache is full, removing an operation from the cache to make a place for the new operation.
            // we will allways remove the operation which its hash code is the first in the vector.
            if (_hashCodes.size() >= _maxSize) {
            
                // removing the file of the operation from the cache directory,
                // and checking if an error has occured while removing the file
                if (remove(getOperationFilePath(*(_hashCodes.begin())).c_str()) != 0) {
                    throw operation::exceptions::FileDeleteException();
                }

                // removing the hash code of the operation from the vector
                _hashCodes.erase(_hashCodes.begin());
            }

            // adding the hash code of the new operation to the vector
            _hashCodes.push_back(operation.getHashCode());

            // if the cache contains the hash code of the operation, moving the hash code of the operation
            // to the end of the vector, according to the LRU algorithm.
            // by moving the hash code of the operation to the end of the vector, we are making 
            // the operation more "relevant", because it makes the operation to stay more time in the cache.
        } else {
            // removing the hash code of the operation from the vector
            _hashCodes.erase(std::find(_hashCodes.begin(), _hashCodes.end(), operation.getHashCode()));
            // pushing the hash code of the operation to the end of the vector
            _hashCodes.push_back(operation.getHashCode());
        }
        
        // writing the new vector into the info file
        // opening the info file using ofstream
        std::ofstream info(_directoryPath + "/info.txt", std::ios::trunc);

        // checking is an error has occured while opening the file
        if (!info.is_open()) {
            throw operation::exceptions::FileOpenException();
        }

        // writing the vector into the info file
        std::for_each(_hashCodes.begin(), _hashCodes.end(), [&info](uint32_t hash) {
            info << hash << '\n';
        });

        // finally, adding the file of the new operation to the cache
        operation.addOperationFileToCache();
    }

    std::string CacheManager::getOperationFilePath(uint32_t hashCode) const {
        // returning the path to the file of the operation with the given hashCode
        return _directoryPath + "/" + std::to_string(hashCode) + ".txt";
    }
}