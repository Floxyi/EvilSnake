#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include <vector>

enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

class Snake {
private:
  std::vector<Vector2> body;
  Direction direction;
  int gridSize;

  bool hasEaten(const Vector2 &foodPosition) const;

public:
  explicit Snake(int grid);
  void setDirection(Direction dir);
  bool moveAndCheckForFood(const Vector2 &foodPosition);
  bool hasCollided() const;
  void draw() const;
  void reset();
  bool isOnSnake(Vector2 position) const;
};

#endif
