#include <cstdint>
#include "Operation.hpp"

namespace cache {
    class CacheManager {
        public:
            bool contains(uint32_t hashCode) const;
            void add(const operation::Operation& operation);
    };
}