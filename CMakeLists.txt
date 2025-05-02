# Minimum required CMake version
cmake_minimum_required(VERSION 3.5)

# Project name and language
project(maze LANGUAGES CXX)

# Set the C++ standard (recommended)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files, which will be used by the final file -> photoshop
add_executable(maze main.cpp input.cpp maze.cpp)