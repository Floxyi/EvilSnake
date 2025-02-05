#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include <vector>

enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

class Snake {
private:
  Direction direction;

  bool hasEaten(const Vector2 &foodPosition) const;

public:
  Snake(const Vector2 &position);

  float speed;
  std::vector<Vector2> body;

  void setDirection(Direction dir);
  bool moveAndCheckForFood(const Vector2 &foodPosition);
  bool hasCollided(const std::vector<Vector2> &foodPosition) const;
  void draw() const;
  void resetToPosition(const Vector2 &position);
};

#endif
