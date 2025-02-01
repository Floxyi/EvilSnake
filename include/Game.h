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

  void update(float deltaTime);
  void reset();
  bool isGameFinished() const;
  void handleInput();
  void handleDirectionChange(Direction dir);

  void draw();
  void drawGrid(int gridSize, Color color);
  void drawGameOverScreen();
  void drawGameFinishedScreen();
  void drawMenuScreen();
  void drawPlayingScreen();

  void takeScreenshot() const;
  Vector2 getRandomGridPosition() const;
  Vector2 getRandomFoodPosition(Snake &snake) const;

public:
  Game(int width, int height, int grid);
  void run();
};

#endif
