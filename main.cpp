#include "CacheManager.hpp"
#include "MatrixOperationFactory.hpp"
#include "HashOperationFactory.hpp"

using namespace operation;

int main() {

    cache::CacheManager cache(3, "cache");

    std::vector<std::string> command = {"hash", "crc32", "hash1.txt", "stdout"};
    HashOperationFactory factory = HashOperationFactory();
    std::unique_ptr<Operation> operation = factory.createOperation(command, cache);
    operation->writeOperationToFile(command[command.size() - 1]);
}