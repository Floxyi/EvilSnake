#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
constexpr float WINDOW_HEIGHT = 600;

constexpr int GRID_Y_AMOUNT = 10;
constexpr float GRID_SIZE = WINDOW_HEIGHT / GRID_Y_AMOUNT;
constexpr float WINDOW_WIDTH = GRID_SIZE * 15;

constexpr float DEFAULT_SNAKE_SPEED = 0.15f;
constexpr float FAST_SNAKE_SPEED = 0.1f;

constexpr float EVENT_PROBABILITY = 10.0f;
constexpr int WALL_AMOUNT = 10;
} // namespace Constants

#endif
