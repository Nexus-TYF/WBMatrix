CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(NTL)

include_directories(include)

aux_source_directory(src/NTL NTL_SRC)
aux_source_directory(src NTL_SRC)

add_library(NTL_LIB ${NTL_SRC})

add_executable(NTL test/NTL_Test.cpp)
add_executable(NtlMat test/matmul_test.cpp)

target_link_libraries(NTL NTL_LIB)
target_link_libraries(NtlMat NTL_LIB)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")