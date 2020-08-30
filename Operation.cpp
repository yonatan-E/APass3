#include "Operation.hpp"
#include "OperationExceptions.hpp"
#include <string>
#include <cstdio>

namespace operation {

    Operation::Operation(uint32_t hashCode) : _hashCode(hashCode) {}

    void Operation::addOperationFileToCache(const cache::CacheManager& cache) const {
        // writing the operation into the file in the cache
        writeOperationToFile(cache.getOperationFilePath(_hashCode));
    }

    uint32_t Operation::getHashCode() const {
        return _hashCode;
    }
}