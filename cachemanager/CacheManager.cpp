#include "CacheManager.hpp"
#include "OperationExceptions.hpp"
#include "MatrixOperationFactory.hpp"
#include "BitmapOperationFactory.hpp"
#include "HashOperationFactory.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sys/stat.h>
#include <unistd.h>

using namespace operation;

namespace cache {

    CacheManager::CacheManager(const uint32_t maxSize,std::string directoryPath)
    : _maxSize(maxSize), _directoryPath(std::move(directoryPath)) {
        
        // checking if the directory exists
        struct stat buffer;
        if (stat(_directoryPath.c_str(), &buffer) != 0) {
            // if the directory doesn't exist, creating a new one
            if (mkdir(_directoryPath.c_str(), 0777) != 0) {
                // throwing an exception in case that the directory creation failed
                throw std::system_error(errno, std::system_category());
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

    void CacheManager::load(const Operation& operation) {
        // if the cache doesn't contain the hash code of the operation, adding the operation to the cache
        if (!contains(operation.getHashCode())) {

            // if the cache is full, removing an operation from the cache to make a place for the new operation.
            // we will allways remove the operation which its hash code is the first in the vector.
            if (_hashCodes.size() >= _maxSize) {
            
                // removing the file of the operation from the cache directory,
                // and checking if an error has occured while removing the file
                if (remove(getOperationFilePath(*(_hashCodes.begin())).c_str()) != 0) {
                    throw exceptions::FileDeleteException();
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
            throw exceptions::FileOpenException();
        }

        // writing the vector into the info file
        for (auto hashCode : _hashCodes) {
            info << hashCode << '\n';
        }

        // finally, adding the file of the new operation to the cache
        operation.writeOperationToFile(getOperationFilePath(operation.getHashCode()));
    }

    bool CacheManager::contains(uint32_t hashCode) const {
        // trying to find the hash code in the vector
        return std::find(_hashCodes.begin(), _hashCodes.end(), hashCode) != _hashCodes.end();
    }

    void CacheManager::clear() {
        // removing all of the result files from the cache directory using for_each
        for_each(_hashCodes.begin(), _hashCodes.end(), [this](uint32_t hashCode) {
            // removing the file of the operation from the cache directory,
            // and checking if an error has occured while removing the file
            if (remove(getOperationFilePath(hashCode).c_str()) != 0) {
                // throwing an exception in case that the directory deletion filed
                throw std::system_error(errno, std::system_category());
            }
        });

        // removing the info.txt file
        if (remove((_directoryPath + "/info.txt").c_str()) != 0) {
            // throwing an exception in case that the directory deletion filed
            throw std::system_error(errno, std::system_category());
        }

        // making the vector empty
        _hashCodes.clear();
    }

    void CacheManager::doCommand(const std::vector<std::string>& command) {

        // the cache command must start with "cache"
        if (command[0] != "cache") {
            throw exceptions::InvalidCommandException();
        }

        // if the given command is "clear", making the cache empty
        if (command[1] == "clear" && command.size() == 2) {
            // clearing the cache
            clear();
            // printing a message about clearing the cache
            std::cout << "Cache was cleared" << std::endl;

            // if the given command is "search", searching for the specified operation
        } else if (command[1] == "search" && (command.size() == 5 || command.size() == 6)) {
            // creating a unique pointer to an operation factory object, which will be initialized
            // according to the specified operation
            std::unique_ptr<OperationFactory> factory;
            // initializing the pointer according to command line arguments
            if (command[2] == "matrix") {
                factory = std::make_unique<MatrixOperationFactory>();
            } else if (command[2] == "image") {
                factory = std::make_unique<BitmapOperationFactory>();
            } else if (command[2] == "hash") {
                factory = std::make_unique<HashOperationFactory>();
            }

            // creating a vector with the operation args
            std::vector<std::string> operationArgs(command.begin() + 3, command.begin() + command.size());
            // getting the hashCode of the specified operation
            uint32_t hashCode;
            try {
                hashCode = factory->calculateOperationHashCode(operationArgs);
            } catch (const exceptions::InvalidCommandException& e) {
                // if catching an invalid command exception, it means that the command is invalid
                throw e;
                return;
            } catch (...) {
                // if catching an another exception, it means that the result of the operation is not in the cache
                std::cout << "Result was not found on cache" << std::endl;
                return;
            }

            // finally checking if the cache contains the specified operation, and printing a message according to that
            if (contains(hashCode)) {
                std::cout << "Result was found on cache" << std::endl;
            } else {
                std::cout << "Result was not found on cache" << std::endl;
            }

            // if the command doesn't uphold anyone of the terms above, it isn't valid
        } else {
            throw exceptions::InvalidCommandException();
        }
    }

    std::string CacheManager::getOperationFilePath(uint32_t hashCode) const {
        // returning the path to the file of the operation with the given hashCode
        return _directoryPath + "/" + std::to_string(hashCode) + ".txt";
    }
}