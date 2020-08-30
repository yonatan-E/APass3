#include "CacheManager.hpp"
#include "MatrixOperationFactory.hpp"

using namespace operation;

int main() {

    cache::CacheManager cache(3, "cache/info.txt");

    std::vector<std::string> command = {"matrix", "add", "matrix1.txt", "matrix2.txt", "stdout"};
    MatrixOperationFactory factory = MatrixOperationFactory();
    std::unique_ptr<Operation> operation = factory.createOperation(command, cache);
    operation->writeOperationToFile(command[4]);
}