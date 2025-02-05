#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <raylib.h>
namespace Constants
{
constexpr int CELL_AMOUNT_Y = 15;
constexpr int CELL_AMOUNT_X = 25;

constexpr float WINDOW_HEIGHT = 600;
constexpr float CELL_SIZE = WINDOW_HEIGHT / CELL_AMOUNT_Y;
constexpr float WINDOW_WIDTH = CELL_SIZE * CELL_AMOUNT_X;

constexpr int WINNING_SCORE = 100;

constexpr float DEFAULT_SNAKE_SPEED = 0.15f;
constexpr float FAST_SNAKE_SPEED = 0.1f;

constexpr float EVENT_INTERVAL = 10.0f;
constexpr int WALL_AMOUNT = 10;

constexpr KeyboardKey KEY_PAUSE = KeyboardKey::KEY_J;
constexpr KeyboardKey KEY_CONTINUE = KeyboardKey::KEY_K;
constexpr KeyboardKey KEY_SCREENSHOT = KeyboardKey::KEY_L;
constexpr KeyboardKey KEY_QUIT = KeyboardKey::KEY_SPACE;
}  // namespace Constants

#endif
