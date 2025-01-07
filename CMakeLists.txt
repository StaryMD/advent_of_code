cmake_minimum_required(VERSION 3.6)

set(CMAKE_COLOR_DIAGNOSTICS
    ON
    CACHE BOOL "")
set(CMAKE_COLOR_MAKEFILE
    ON
    CACHE BOOL "")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(MY_CPP_VERSION
    20
    CACHE STRING "")

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(aoc)

add_subdirectory(src)
