CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(M4RIMatrix)

include_directories(include)

aux_source_directory(src/m4ri M4RI_SRC)
aux_source_directory(src/matrixlib M4RI_SRC)

add_library(M4RI_LIB ${M4RI_SRC})

add_executable(M4RI test/M4RI_test.c)
add_executable(MULTEST test/matmul_test.c)

target_link_libraries(M4RI M4RI_LIB)
target_link_libraries(MULTEST M4RI_LIB)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2")