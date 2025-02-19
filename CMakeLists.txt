cmake_minimum_required(VERSION 3.10)
project(EvilSnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/main.cpp
    src/game.cpp
    src/snake.cpp
    src/text_utils.cpp
    src/game_utils.cpp
    src/sound_manager.cpp
    src/font_manager.cpp
    src/screen_manager.cpp
)

include_directories(src)

add_executable(EvilSnake ${SOURCES})

find_package(raylib REQUIRED)
target_link_libraries(EvilSnake raylib)
