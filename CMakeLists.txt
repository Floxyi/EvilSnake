cmake_minimum_required(VERSION 3.10)
project(EvilSnake VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(raylib REQUIRED)

add_executable(game src/main.cpp)

target_link_libraries(game raylib)
