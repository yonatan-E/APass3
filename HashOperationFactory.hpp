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
             * @brief Create an operation object
             * 
             * @param command the command to create the operation object from
             * @param cache a cache manager
             * @return std::unique_ptr<Operation> a unique pointer to the operation
             */
            virtual std::unique_ptr<Operation> createOperation(const std::vector<std::string>& command,
                cache::CacheManager& cache) const override;

        private:

            /**
             * @brief Get the hashCode of the hash operation
             * 
             * @param arg the CrcHash argument
             * @return uint32_t the hashCode of the operation
             */
            static uint32_t getOperationHashCode(const hash::CrcHash& arg);

            /**
             * @brief Read a CrcHash object from a file
             * 
             * @param pathToFile the file path
             * @return hash::CrcHash the CrcHash which was read from the file
             */
            static hash::CrcHash readHashFromFile(const std::string& pathToFile);
    };
}