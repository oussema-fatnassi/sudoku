cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a library for your project
add_library(my_project_lib grid.cpp)

# Create a test executable
add_executable(my_project_test test.cpp)

# Find the Google Test package
find_package(GTest REQUIRED)

# Link the test executable to the project library and Google Test
target_link_libraries(my_project_test my_project_lib GTest::GTest GTest::Main)

# Enable testing
enable_testing()