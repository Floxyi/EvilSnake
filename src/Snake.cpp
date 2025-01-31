#include "../include/Snake.h"
#include "raylib.h"

Snake::Snake(int grid) : gridSize(grid), direction(Direction::NONE) {
  body.push_back({gridSize * 5, gridSize * 5});
}

void Snake::setDirection(Direction dir) {
  bool oppositeRight = direction == Direction::RIGHT && dir == Direction::LEFT;
  bool oppositeLeft = direction == Direction::LEFT && dir == Direction::RIGHT;
  bool oppositeUp = direction == Direction::UP && dir == Direction::DOWN;
  bool oppositeDown = direction == Direction::DOWN && dir == Direction::UP;

  if (!oppositeRight && !oppositeLeft && !oppositeUp && !oppositeDown) {
    direction = dir;
  }
}

bool Snake::move(const Position &foodPosition) {
  Position head = body.front();

  switch (direction) {
  case Direction::UP:
    head.y -= gridSize;
    break;
  case Direction::DOWN:
    head.y += gridSize;
    break;
  case Direction::LEFT:
    head.x -= gridSize;
    break;
  case Direction::RIGHT:
    head.x += gridSize;
    break;
  default:
    break;
  }

  head.x = (head.x + GetScreenWidth()) % GetScreenWidth();
  head.y = (head.y + GetScreenHeight()) % GetScreenHeight();
  body.insert(body.begin(), head);

  if (head.x == foodPosition.x && head.y == foodPosition.y) {
    return true;
  } else {
    body.pop_back();
    return false;
  }
}

bool Snake::hasCollided() const {
  const Position &head = body.front();
  for (size_t i = 1; i < body.size(); ++i) {
    if (body[i].x == head.x && body[i].y == head.y) {
      return true;
    }
  }
  return false;
}

void Snake::draw() const {
  for (const Position &bodyPart : body) {
    DrawRectangle(bodyPart.x, bodyPart.y, gridSize, gridSize, DARKGREEN);
  }
}

void Snake::reset() {
  body.clear();
  body.push_back({gridSize * 5, gridSize * 5});
  direction = Direction::RIGHT;
}

bool Snake::isOnSnake(Position position) const {
  for (const Position &bodyPart : body) {
    if (bodyPart.x == position.x && bodyPart.y == position.y) {
      return true;
    }
  }
  return false;
}
