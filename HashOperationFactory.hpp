#include "OperationFactory.hpp"
#include "HashOperation.hpp"

namespace operation {

    class HashOperationFactory : public OperationFactory{

        public:

            virtual std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const override;

        protected:

            virtual bool isValidCommand(const std::vector<std::string>& command) const override;

        private:

            static uint32_t getOperationHashCode(const hash::CrcHash& arg);

            static hash::CrcHash readHashFromFile(const std::string& pathToFile);
    };
}