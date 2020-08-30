#include "CacheManager.hpp"
#include "BitmapOperationFactory.hpp"

using namespace operation;

int main() {
    cache::CacheManager cache(3, "cache");
    std::vector<std::string> command = {"image", "rotate", "lena-color.bmp", "copy.bmp"};

    BitmapOperationFactory bof = BitmapOperationFactory();
    std::unique_ptr<Operation> op = bof.createOperation(command, cache);
    op->writeOperationToFile(command[3]);
}