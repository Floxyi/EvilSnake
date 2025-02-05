#include "../include/Snake.h"

#include "../include/Constants.h"
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

    if (head.x == foodPosition.x && head.y == foodPosition.y) {
        return true;
    } else {
        body.pop_back();
        return false;
    }
}

bool Snake::hasCollided(const std::vector<Vector2> &wallPositions) const
{
    const Vector2 &head = body.front();
    for (size_t i = 3; i < body.size(); ++i) {
        if (body[i].x == head.x && body[i].y == head.y) {
            return true;
        }
    }
    for (const Vector2 &wallPosition : wallPositions) {
        if (head.x == wallPosition.x && head.y == wallPosition.y) {
            return true;
        }
    }
    return false;
}

void Snake::draw() const
{
    for (const Vector2 &bodyPart : body) {
        DrawRectangle(bodyPart.x, bodyPart.y, Constants::CELL_SIZE, Constants::CELL_SIZE, DARKGREEN);
    }
}

void Snake::resetToPosition(const Vector2 &position)
{
    body.clear();
    body.push_back(position);
    direction = Direction::RIGHT;
}
