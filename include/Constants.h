#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <raylib.h>
namespace Constants {
constexpr float WINDOW_HEIGHT = 600;

constexpr int GRID_Y_AMOUNT = 10;
constexpr float GRID_SIZE = WINDOW_HEIGHT / GRID_Y_AMOUNT;
constexpr float WINDOW_WIDTH = GRID_SIZE * 15;

constexpr float DEFAULT_SNAKE_SPEED = 0.15f;
constexpr float FAST_SNAKE_SPEED = 0.1f;

constexpr float EVENT_PROBABILITY = 10.0f;
constexpr int WALL_AMOUNT = 10;

constexpr KeyboardKey KEY_PAUSE = KeyboardKey::KEY_J;
constexpr KeyboardKey KEY_CONTINUE = KeyboardKey::KEY_K;
constexpr KeyboardKey KEY_SCREENSHOT = KeyboardKey::KEY_L;
constexpr KeyboardKey KEY_QUIT = KeyboardKey::KEY_SPACE;
} // namespace Constants

#endif
