CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(WBMatrix)

include_directories(include)

aux_source_directory(src WBM_SRC)

add_library(WB_LIB ${WBM_SRC})

add_executable(BMM test/BasisMatrixMethod_test.c)
add_executable(WBMM test/WBMatrixMethod_test.c)
add_executable(RGEM test/RGEMethod_test.c)
add_executable(WBGEM test/WBGEMethod_test.c)
add_executable(RLUDM test/RLUDMethod_test.c)

target_link_libraries(BMM WB_LIB)
target_link_libraries(WBMM WB_LIB)
target_link_libraries(RGEM WB_LIB)
target_link_libraries(WBGEM WB_LIB)
target_link_libraries(RLUDM WB_LIB)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2")