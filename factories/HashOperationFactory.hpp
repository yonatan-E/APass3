#include "OperationFactory.hpp"
#include "HashOperation.hpp"

namespace operation {

    /**
     * @brief This class is in charge of creating HashOperation objects.
     * 
     */
    class HashOperationFactory : public OperationFactory {

        public:

            /**
             * @brief Create an operation object according to a command
             * 
             * @param command the command to create the operation object from
             * @param cache a cache manager
             * @return std::unique_ptr<Operation> a unique pointer to the operation
             */
            std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const override;

            /**
             * @brief Get the hashCode of an operation
             * 
             * @param operationArgs the operation args:
             *                      operationArgs[0] - the operation type, which can be only crc32 (open to extensions)
             *                      operationArgs[1] - the path to the input bin file
             * @return uint32_t the hashCode of the operation
             */
            uint32_t calculateOperationHashCode(const std::vector<std::string>& operationArgs) const override;

        private:

            /**
             * @brief Read a CrcHash object from a file
             * 
             * @param pathToFile the file path
             * @return hash::CrcHash the CrcHash which was read from the file
             */
            static hash::CrcHash readCrcHashFromFile(const std::string& pathToFile);
    };
}