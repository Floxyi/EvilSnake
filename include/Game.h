#ifndef GAME_H
#define GAME_H

#include "GameMode.h"
#include "GameState.h"
#include "Snake.h"
#include "raylib.h"

class Game {
private:
  GameState state;
  GameMode mode;
  Snake snake;
  Vector2 foodPosition;
  std::vector<Vector2> wallPositions;
  int score;
  float startTime;
  float endTime;
  float timeSinceLastMove;
  float timeSinceLastEventCheck;

  void update();
  void reset();
  void changeGameMode();
  bool isGameFinished() const;
  void handleInput();
  void handleDirectionChange(Direction dir);

  void draw();
  void drawGrid(Color color);

public:
  Game();
  void run();
};

#endif
