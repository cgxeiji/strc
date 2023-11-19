project(example_strc)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Werror")

add_executable(example_strc main.cpp)

set_property(TARGET example_strc PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

target_sources(example_strc PRIVATE
    ./strc.cpp
)


