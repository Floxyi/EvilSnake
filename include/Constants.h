#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"

namespace Constants {
constexpr int WINDOW_HEIGHT = 600;

constexpr int GRID_Y_AMOUNT = 10;
constexpr int GRID_SIZE = WINDOW_HEIGHT / GRID_Y_AMOUNT;
constexpr int WINDOW_WIDTH = GRID_SIZE * 15;

constexpr float SNAKE_SPEED = 0.15f;

constexpr Color BACKGROUND_COLOR = RAYWHITE;
} // namespace Constants

#endif
