cmake_minimum_required(VERSION 3.5)
project(sudoku)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_GENERATOR "MinGW Makefiles")

add_executable(sudoku main.cpp grid.cpp)