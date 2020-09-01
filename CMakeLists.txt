cmake_minimum_required(VERSION 3.0.0)
project(ex3 VERSION 0.1.0)

include(CTest)
set(C_STANDARD C99)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

set(HEADER_FILES cachemanager/CacheManager.hpp hash/crc32.h hash/CrcHash.hpp matrix/Matrix.hpp matrix/ErrorCode.hpp
bitmap/BitAdjuster.hpp bitmap/Bitmap.hpp bitmap/BitmapHeader.hpp bitmap/BitmapDIBHeader.hpp bitmap/BitmapArray.hpp bitmap/ColorPallete.hpp
operations/Operation.hpp operations/MatrixOperation.hpp operations/BitmapOperation.hpp operations/HashOperation.hpp 
factories/MatrixOperationFactory.hpp factories/BitmapOperationFactory.hpp factories/HashOperationFactory.hpp 
exceptions/OperationExceptions.hpp)

include_directories(${CMAKE_SOURCE_DIR}/matrix ${CMAKE_SOURCE_DIR}/bitmap ${CMAKE_SOURCE_DIR}/hash
${CMAKE_SOURCE_DIR}/operation ${CMAKE_SOURCE_DIR}/factories ${CMAKE_SOURCE_DIR}/cachemanager)
link_directories(${CMAKE_SOURCE_DIR}/bin)
add_executable(ex3 main.cpp cachemanager/CacheManager.cpp hash/crc32.c hash/CrcHash.cpp matrix/Matrix.cpp matrix/ErrorCode.cpp
bitmap/BitAdjuster.cpp bitmap/Bitmap.cpp bitmap/BitmapHeader.cpp bitmap/BitmapDIBHeader.cpp bitmap/BitmapArray.cpp bitmap/ColorPallete.cpp
operations/Operation.cpp operations/MatrixOperation.cpp operations/BitmapOperation.cpp operations/HashOperation.cpp 
factories/MatrixOperationFactory.cpp factories/BitmapOperationFactory.cpp factories/HashOperationFactory.cpp 
exceptions/OperationExceptions.cpp)
target_include_directories(ex3 PRIVATE ${CMAKE_SOURCE_DIR}/operations ${CMAKE_SOURCE_DIR}/exceptions)
target_link_libraries(ex3 matrix)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
