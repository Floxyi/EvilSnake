#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "raylib.h"

enum class GameState { MENU, PLAYING, FINISHED, GAME_OVER };

class Game {
private:
  int windowWidth;
  int windowHeight;
  int gridSize;
  GameState state;
  Snake snake;
  Vector2 foodPosition;
  int score;
  float startTime;
  float timeSinceLastMove;

  void handleInput();
  void update(float deltaTime);
  void draw();
  void drawGrid(int gridSize, Color color);
  void drawGameOverScreen();
  void drawGameFinishedScreen();
  void drawMenuScreen();
  void drawPlayingScreen();
  void reset();
  bool isGameFinished() const;

public:
  Game(int width, int height, int grid);
  void run();
};

#endif
