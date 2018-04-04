cmake_minimum_required(VERSION 3.10)
project("Project Euler")

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(solutions)
add_subdirectory(utils)

include_directories(utils)
