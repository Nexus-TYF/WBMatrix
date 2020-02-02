CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(InvMatrix)

include_directories(include)

aux_source_directory(src InvM_SRC)

add_library(InvM_LIB ${InvM_SRC})

add_executable(InvM test/InvMatrix_test.c)

target_link_libraries(InvM InvM_LIB)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2")