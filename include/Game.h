#ifndef GAME_H
#define GAME_H

#include "game_mode.h"
#include "game_state.h"
#include "raylib.h"
#include "snake.h"

class Game
{
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
    void handleInput();
    void handleDirectionChange(Direction dir);

    void draw();
    void drawGrid();
    void drawGameObjects();
    void drawUI();

   public:
    Game();
    void run();
};

#endif
