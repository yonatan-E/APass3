cmake_minimum_required(VERSION 3.0.0)
project(cache_tester VERSION 0.1.0)

include(CTest)
set(C_STANDARD C99)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/matrix ${CMAKE_SOURCE_DIR}/hash)
link_directories(${CMAKE_SOURCE_DIR}/matrix)
add_executable(cache_tester main.cpp CacheManager.cpp hash/crc32.c hash/CrcHash.cpp matrix/ErrorCode.cpp matrix/Matrix.cpp 
HashOperation.cpp MatrixOperation.cpp Operation.cpp HashOperationFactory.cpp MatrixOperationFactory.cpp OperationExceptions.cpp)
target_link_libraries(cache_tester matrix)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
