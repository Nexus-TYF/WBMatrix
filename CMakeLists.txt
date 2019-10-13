CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(matrix)

include_directories(include)

aux_source_directory(src/WBMatrix WBM_SRC)

aux_source_directory(src/m4ri M4RI)

add_library(WB_LIB ${WBM_SRC})

add_library(M4RI_LIB ${M4RI})

add_executable(P_TEST test/Performance_test.c)

target_link_libraries(P_TEST WB_LIB M4RI_LIB)


