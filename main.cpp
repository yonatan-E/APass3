#include "CacheManager.hpp"
#include "MatrixOperationFactory.hpp"
#include "BitmapOperationFactory.hpp"
#include "HashOperationFactory.hpp"
#include <iostream>

using namespace operation;

int main() {
    try {
        cache::CacheManager cache(3, "cache");

        std::vector<std::string> command = {"matrix", "add", "matrix1.txt", "matrix2.txt", "stdout"};
        std::unique_ptr<OperationFactory> factory;
        if (command[0] == "matrix") {
            factory = std::make_unique<MatrixOperationFactory>();
        } else if (command[0] == "image") {
            factory = std::make_unique<BitmapOperationFactory>();
        } else if (command[0] == "hash") {
            factory = std::make_unique<HashOperationFactory>();
        }

        std::unique_ptr<Operation> operation = factory->createOperation(command, cache);
        operation->writeOperationToFile(command[command.size() - 1]);
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << '\n';
    }
}