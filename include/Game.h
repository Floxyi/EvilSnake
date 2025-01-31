#ifndef GAME_H
#define GAME_H

#include "Position.h"
#include "Snake.h"
#include "raylib.h"

enum class GameState { MENU, PLAYING, GAME_OVER };

class Game {
private:
  int windowWidth;
  int windowHeight;
  int gridSize;
  GameState state;
  Snake snake;
  Position foodPosition;
  int score;
  float timeSinceLastMove;

  void handleInput();
  void update(float deltaTime);
  void draw();
  void drawGrid(int gridSize, Color color);
  void drawGameOverScreen();
  void drawMenuScreen();
  void drawPlayingScreen();
  void reset();

public:
  Game(int width, int height, int grid);
  void run();
};

#endif
