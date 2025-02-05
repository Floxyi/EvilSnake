cmake_minimum_required(VERSION 3.10)
project(EvilSnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Snake.cpp
    src/TextUtils.cpp
    src/GameUtils.cpp
    src/SoundManager.cpp
    src/FontManager.cpp
    src/ScreenManager.cpp
)

include_directories(src)

add_executable(EvilSnake ${SOURCES})

find_package(raylib REQUIRED)
target_link_libraries(EvilSnake raylib)
