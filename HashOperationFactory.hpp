#include "OperationFactory.hpp"
#include "HashOperation.hpp"

namespace operation{

    class HashOperationFactory : public OperationFactory{

        public:

            virtual std::unique_ptr<Operation> createOperation(const std::string command[]) const override;

        protected:

            virtual bool isValidCommand(const std::string command[]) const override;

        private:

            static hash::CrcHash readHashFromFile(const std::string& pathToFile);
    };
}