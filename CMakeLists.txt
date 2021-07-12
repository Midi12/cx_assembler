cmake_minimum_required(VERSION 3.19)
project(cx_assembler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O2")

add_executable(cx_assembler_tests tests/main.cpp)

add_executable(cx_assembler_example_basic examples/example_basic.cpp)
add_executable(cx_assembler_example_basic_bis examples/example_basic_bis.cpp)
add_executable(cx_assembler_example_opaque_compute examples/example_opaque_compute.cpp)