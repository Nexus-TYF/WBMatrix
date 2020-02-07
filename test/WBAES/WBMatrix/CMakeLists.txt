CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(WBAES)

include_directories(include)

aux_source_directory(src/WBMatrix WBAES_SRC)
aux_source_directory(src/ WBAES_SRC)

add_library(WBAES_LIB ${WBAES_SRC})

add_executable(WBAES test/main.cpp)

target_link_libraries(WBAES WBAES_LIB)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")