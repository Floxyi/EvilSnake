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

if(MACOS_BUILD)
    include(FetchContent)

    # Ensure raylib is built as a static library
    set(BUILD_SHARED_LIBS OFF)
    set(FETCHCONTENT_QUIET OFF)

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
    )

    FetchContent_MakeAvailable(raylib)

    add_definitions(-DMACOS_BUILD)
else()
    find_package(raylib REQUIRED)
endif()

add_executable(EvilSnake ${SOURCES})

if(MACOS_BUILD)
    target_link_libraries(EvilSnake raylib m)
else()
    target_link_libraries(EvilSnake raylib)
endif()
