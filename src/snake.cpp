/**
 * @file snake.cpp
 * @brief Implementation of the Snake class for the Evil Snake game
 *
 * This file defines the behavior of the snake, including movement, collision detection,
 * rendering, and game interactions such as eating food and resetting position.
 */

#include "../include/snake.h"

#include "../include/constants.h"
#include "raylib.h"

/**
 * @brief Constructs a Snake object with an initial position.
 *
 * @param position The starting position of the snake.
 */
Snake::Snake(const Vector2 &position)
    : speed(Constants::DEFAULT_SNAKE_SPEED), direction(Direction::NONE), body{position}
{
}

/**
 * @brief Sets the movement direction of the snake.
 *
 * Prevents the snake from reversing direction directly.
 *
 * @param dir The new direction to set.
 */
void Snake::setDirection(Direction dir)
{
    bool oppositeRight = direction == Direction::RIGHT && dir == Direction::LEFT;
    bool oppositeLeft = direction == Direction::LEFT && dir == Direction::RIGHT;
    bool oppositeUp = direction == Direction::UP && dir == Direction::DOWN;
    bool oppositeDown = direction == Direction::DOWN && dir == Direction::UP;

    if (!oppositeRight && !oppositeLeft && !oppositeUp && !oppositeDown) {
        direction = dir;
    }
}

/**
 * @brief Moves the snake and checks if it has eaten food.
 *
 * Moves the snake in its current direction, handling screen wrapping.
 * If the snake eats food, it grows; otherwise, it moves normally.
 *
 * @param foodPosition The position of the food on the grid.
 * @return true if the snake eats the food, false otherwise.
 */
bool Snake::moveAndCheckForFood(const Vector2 &foodPosition)
{
    Vector2 head = body.front();

    switch (direction) {
        case Direction::UP:
            head.y -= Constants::CELL_SIZE;
            break;
        case Direction::DOWN:
            head.y += Constants::CELL_SIZE;
            break;
        case Direction::LEFT:
            head.x -= Constants::CELL_SIZE;
            break;
        case Direction::RIGHT:
            head.x += Constants::CELL_SIZE;
            break;
        default:
            break;
    }

    // Handle screen wrapping
    head.x = (int) (head.x + GetScreenWidth()) % GetScreenWidth();
    head.y = (int) (head.y + GetScreenHeight()) % GetScreenHeight();
    body.insert(body.begin(), head);

    bool ateFood = (head.x == foodPosition.x && head.y == foodPosition.y);
    if (!ateFood) {
        body.pop_back();
    }
    return ateFood;
}

/**
 * @brief Checks if the snake has collided with itself or a wall.
 *
 * @param wallPositions Vector containing the positions of walls.
 * @return true if the snake collides with itself or a wall, false otherwise.
 */
bool Snake::hasCollided(const std::vector<Vector2> &wallPositions) const
{
    // Check self-collision
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i].x == body.front().x && body[i].y == body.front().y) {
            return true;
        }
    }

    // Check wall collision
    if (std::any_of(wallPositions.begin(), wallPositions.end(),
            [&](const Vector2 &wall) { return wall.x == body.front().x && wall.y == body.front().y; })) {
        return true;
    }

    return false;
}

/**
 * @brief Draws the snake on the screen.
 *
 * The snake's head is colored green, while the body is a darker green.
 */
void Snake::draw() const
{
    for (size_t i = 0; i < body.size(); ++i) {
        DrawRectangle(body[i].x, body[i].y, Constants::CELL_SIZE, Constants::CELL_SIZE, i == 0 ? GREEN : DARKGREEN);
    }
}

/**
 * @brief Resets the snake to a given position and default direction.
 *
 * @param position The position to reset the snake to.
 */
void Snake::resetToPosition(const Vector2 &position)
{
    body.assign(1, position);
    direction = Direction::RIGHT;
}
