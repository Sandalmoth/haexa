cmake_minimum_required(VERSION 3.0.0)

add_executable(scratch scratch.cpp)

# Libraries

# Compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -ggdb") # debug compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
