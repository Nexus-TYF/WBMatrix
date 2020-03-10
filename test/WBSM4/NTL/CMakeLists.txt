CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(WBSM4)

include_directories(include)

aux_source_directory(src/NTL WBSM4_SRC)
aux_source_directory(src/matrixlib WBSM4_SRC)

add_library(WBSM4_LIB ${WBSM4_SRC})

add_executable(WBSM4 test/main.cpp)

target_link_libraries(WBSM4 WBSM4_LIB)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")