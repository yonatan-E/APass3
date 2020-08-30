cmake_minimum_required(VERSION 3.0.0)
project(cache_tester VERSION 0.1.0)

include(CTest)
set(C_STANDARD C99)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/matrix ${CMAKE_SOURCE_DIR}/bitmap)
link_directories(${CMAKE_SOURCE_DIR}/matrix)
add_executable(cache_tester main.cpp CacheManager.cpp crc32.c CrcHash.cpp matrix/ErrorCode.cpp matrix/Matrix.cpp 
BitmapOperation.cpp Operation.cpp BitmapOperationFactory.cpp OperationExceptions.cpp bitmap/Bitmap.cpp
bitmap/BitmapArray.cpp bitmap/BitmapHeader.cpp bitmap/BitmapDIBHeader.cpp bitmap/ColorPallete.cpp bitmap/BitAdjuster.cpp)
target_link_libraries(cache_tester matrix)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
