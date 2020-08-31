cmake_minimum_required(VERSION 3.0.0)
project(ex3 VERSION 0.1.0)

include(CTest)
set(C_STANDARD C99)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
include_directories(${CMAKE_SOURCE_DIR}/matrix ${CMAKE_SOURCE_DIR}/bitmap ${CMAKE_SOURCE_DIR}/hash)
link_directories(${CMAKE_SOURCE_DIR}/bin)
add_executable(ex3 main.cpp CacheManager.cpp hash/crc32.c hash/CrcHash.cpp matrix/Matrix.cpp matrix/ErrorCode.cpp
bitmap/BitAdjuster.cpp bitmap/Bitmap.cpp bitmap/BitmapHeader.cpp bitmap/BitmapDIBHeader.cpp bitmap/BitmapArray.cpp bitmap/ColorPallete.cpp
Operation.cpp MatrixOperation.cpp BitmapOperation.cpp HashOperation.cpp MatrixOperationFactory.cpp BitmapOperationFactory.cpp HashOperationFactory.cpp 
OperationExceptions.cpp)
target_link_libraries(ex3 matrix)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
