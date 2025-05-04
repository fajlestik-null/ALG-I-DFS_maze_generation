cmake_minimum_required(VERSION 3.5)

project(maze LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

add_executable(maze main.cpp input.cpp maze.cpp)