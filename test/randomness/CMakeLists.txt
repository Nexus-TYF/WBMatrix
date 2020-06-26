CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(WBMatrix)

include_directories(include)

aux_source_directory(src/WBMatrix WBM_SRC)

add_library(WB_LIB ${WBM_SRC})

add_executable(RT Randomness_test.c)

target_link_libraries(RT WB_LIB)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2")