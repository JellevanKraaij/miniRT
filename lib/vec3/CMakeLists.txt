cmake_minimum_required(VERSION 3.21.0)

project(libvec3)
set (SRCS
	src/add.c
	src/multiply.c
	src/subtract.c
	src/scalar.c
	src/utils.c
	src/new.c
	src/dot.c
)

add_library(vec3 STATIC ${SRCS})
target_include_directories(vec3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
