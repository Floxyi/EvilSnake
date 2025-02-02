#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "raylib.h"

enum class GameState { MENU, PLAYING, PAUSED, FINISHED, GAME_OVER };
enum class GameMode { NORMAL, FAST, WALLS };

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

  void init();
  void update();
  void reset();
  void changeGameMode();
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
  Vector2 getRandomWallPosition(Snake &snake) const;
  std::string getFormattedGameTime(float until) const;
  std::string getFormattedGameMode() const;

public:
  Game();
  void run();
};

#endif
