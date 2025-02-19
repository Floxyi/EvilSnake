#include "../include/snake.h"

#include "../include/constants.h"
#include "raylib.h"

Snake::Snake(const Vector2 &position)
    : speed(Constants::DEFAULT_SNAKE_SPEED), direction(Direction::NONE), body{position}
{
}

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

    head.x = (int) (head.x + GetScreenWidth()) % GetScreenWidth();
    head.y = (int) (head.y + GetScreenHeight()) % GetScreenHeight();
    body.insert(body.begin(), head);

    bool ateFood = (head.x == foodPosition.x && head.y == foodPosition.y);
    if (!ateFood) {
        body.pop_back();
    }
    return ateFood;
}

bool Snake::hasCollided(const std::vector<Vector2> &wallPositions) const
{
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i].x == body.front().x && body[i].y == body.front().y) {
            return true;
        }
    }

    if (std::any_of(wallPositions.begin(), wallPositions.end(),
            [&](const Vector2 &wall) { return wall.x == body.front().x && wall.y == body.front().y; })) {
        return true;
    }

    return false;
}

void Snake::draw() const
{
    for (size_t i = 0; i < body.size(); ++i) {
        DrawRectangle(body[i].x, body[i].y, Constants::CELL_SIZE, Constants::CELL_SIZE, i == 0 ? GREEN : DARKGREEN);
    }
}

void Snake::resetToPosition(const Vector2 &position)
{
    body.assign(1, position);
    direction = Direction::RIGHT;
}
