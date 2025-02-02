#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "raylib.h"

enum class GameState { MENU, PLAYING, PAUSED, FINISHED, GAME_OVER };

class Game {
private:
  GameState state;
  Snake snake;
  Vector2 foodPosition;
  int score;
  float startTime;
  float endTime;
  float timeSinceLastMove;

  void init();
  void update();
  void reset();
  bool isGameFinished() const;
  void handleInput();
  void handleDirectionChange(Direction dir);

  void draw();
  void drawGrid(Color color);
  void drawGameOverScreen();
  void drawGameFinishedScreen();
  void drawMenuScreen();
  void drawPlayingScreen();
  void drawPauseScreen();

  void takeScreenshot() const;
  Vector2 getRandomGridPosition() const;
  Vector2 getRandomFoodPosition(Snake &snake) const;
  std::string getFormattedGameTime(float until) const;

public:
  Game();
  void run();
};

#endif
