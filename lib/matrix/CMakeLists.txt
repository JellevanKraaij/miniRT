cmake_minimum_required(VERSION 3.21.0)

project(libmatrix)
set (SRCS
    src/allocation.c
    src/utils.c
    src/matrix.c
    src/addition.c
    src/subtraction.c
    src/multiplication.c
    src/checks.c
)

add_library(matrix STATIC ${SRCS})
target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
