#include "CacheManager.hpp"
#include "MatrixOperationFactory.hpp"
#include "BitmapOperationFactory.hpp"
#include "HashOperationFactory.hpp"
#include <iostream>

using namespace operation;

int main(int argc, char *argv[]) {

    // converting the command line arguments into a vector
    std::vector<std::string> command(argv + 1, argv + argc);

    try {

        // creating a new cache manager in size 5, which its data will be saved at the directory "cache"
        cache::CacheManager cache(3, "cache");

        // creating a unique pointer to an operation factory object, which will be initialized by runtime
        std::unique_ptr<OperationFactory> factory;
        // initializing the pointer according to command line arguments
        if (command[0] == "matrix") {
            factory = std::make_unique<MatrixOperationFactory>();
        } else if (command[0] == "image") {
            factory = std::make_unique<BitmapOperationFactory>();
        } else if (command[0] == "hash") {
            factory = std::make_unique<HashOperationFactory>();
        }

        // getting the operation object from the factory
        std::unique_ptr<Operation> operation = factory->createOperation(command, cache);
        // writing the operation to the output file
        operation->writeOperationToFile(command[command.size() - 1]);

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}