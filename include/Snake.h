#ifndef SNAKE_H
#define SNAKE_H

#include "Position.h"
#include <vector>

enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

class Snake {
private:
  std::vector<Position> body;
  Direction direction;
  int gridSize;

  bool hasEaten(const Position &foodPosition) const;

public:
  explicit Snake(int grid);
  void setDirection(Direction dir);
  bool move(const Position &foodPosition);
  bool hasCollided() const;
  void draw() const;
  void reset();
  bool isOnSnake(Position position) const;
};

#endif
