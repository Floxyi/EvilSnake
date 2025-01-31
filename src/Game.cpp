#include "../include/Game.h"
#include "../include/Constants.h"
#include "../include/Utils.h"
#include "raylib.h"

Game::Game(int width, int height, int gridSize)
    : windowWidth(width), windowHeight(height), gridSize(gridSize),
      state(GameState::MENU), score(0), timeSinceLastMove(0.0f),
      snake(gridSize) {
  foodPosition =
      Utils::getRandomGridPosition(gridSize, windowWidth, windowHeight);
}

void Game::reset() {
  this->score = 0;
  this->snake.reset();
  state = GameState::MENU;
}

void Game::handleInput() {
  if (state == GameState::PLAYING && IsKeyPressed(KEY_SPACE)) {
    reset();
  }

  if (state == GameState::GAME_OVER && IsKeyPressed(KEY_SPACE)) {
    reset();
  }

  if (state == GameState::PLAYING || state == GameState::MENU) {
    if (IsKeyPressed(KEY_UP)) {
      if (state == GameState::MENU) {
        state = GameState::PLAYING;
      }
      snake.setDirection(Direction::UP);
    }
    if (IsKeyPressed(KEY_DOWN)) {
      if (state == GameState::MENU) {
        state = GameState::PLAYING;
      }
      snake.setDirection(Direction::DOWN);
    }
    if (IsKeyPressed(KEY_LEFT)) {
      if (state == GameState::MENU) {
        state = GameState::PLAYING;
      }
      snake.setDirection(Direction::LEFT);
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      if (state == GameState::MENU) {
        state = GameState::PLAYING;
      }
      snake.setDirection(Direction::RIGHT);
    }
  }
}

void Game::update(float deltaTime) {
  if (state == GameState::PLAYING) {
    timeSinceLastMove += deltaTime;

    if (timeSinceLastMove >= Constants::SNAKE_SPEED) {
      timeSinceLastMove = 0.0f;

      if (snake.move(foodPosition)) {
        score++;
        foodPosition =
            Utils::getRandomGridPosition(gridSize, windowWidth, windowHeight);
      }

      if (snake.hasCollided()) {
        state = GameState::GAME_OVER;
      }
    }
  }
}

void Game::drawGrid(int gridSize, Color color) {
  for (int x = 0; x < windowWidth; x += gridSize) {
    DrawLine(x, 0, x, windowHeight, color);
  }
  for (int y = 0; y < windowHeight; y += gridSize) {
    DrawLine(0, y, windowWidth, y, color);
  }
}

void Game::drawGameOverScreen() {
  Utils::drawAlignedText("GAME OVER", 40, DARKGRAY, VerticalAlignment::CENTER,
                         HorizontalAlignment::CENTER, -100, windowWidth,
                         windowHeight);
  Utils::drawAlignedText(
      (std::string("Score: ") + std::to_string(score)).c_str(), 20, DARKGRAY,
      VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50, windowWidth,
      windowHeight);
  Utils::drawAlignedText("Press the [SPACE] key to get back to the menu", 20,
                         DARKGRAY, VerticalAlignment::CENTER,
                         HorizontalAlignment::CENTER, 50, windowWidth,
                         windowHeight);
}

void Game::drawMenuScreen() {
  Utils::drawAlignedText("Welcome to EvilSnake!", 40, DARKGRAY,
                         VerticalAlignment::TOP, HorizontalAlignment::CENTER,
                         50, windowWidth, windowHeight);
  Utils::drawAlignedText("Press the [UP ARROW] key to start the game", 20,
                         DARKGRAY, VerticalAlignment::TOP,
                         HorizontalAlignment::CENTER, 120, windowWidth,
                         windowHeight);
  Utils::drawAlignedText("(play with arrow keys)", 20, DARKGRAY,
                         VerticalAlignment::TOP, HorizontalAlignment::CENTER,
                         150, windowWidth, windowHeight);
  Utils::drawAlignedText("Made by Florian", 20, DARKGRAY,
                         VerticalAlignment::BOTTOM, HorizontalAlignment::LEFT,
                         10, windowWidth, windowHeight);
  Utils::drawAlignedText("[ESC] - Quit", 20, DARKGRAY,
                         VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER,
                         10, windowWidth, windowHeight);
  Utils::drawAlignedText("v1.0", 20, DARKGRAY, VerticalAlignment::BOTTOM,
                         HorizontalAlignment::RIGHT, 10, windowWidth,
                         windowHeight);
}

void Game::drawPlayingScreen() {
  Utils::drawAlignedText(
      (std::string("Score: ") + std::to_string(score)).c_str(), 20, DARKGRAY,
      VerticalAlignment::TOP, HorizontalAlignment::LEFT, 10, windowWidth,
      windowHeight);
  Utils::drawAlignedText("Press the [SPACE] key to get back to the menu", 20,
                         DARKGRAY, VerticalAlignment::BOTTOM,
                         HorizontalAlignment::CENTER, 10, windowWidth,
                         windowHeight);
}

void Game::draw() {
  ClearBackground(Constants::BACKGROUND_COLOR);
  drawGrid(gridSize, LIGHTGRAY);
  DrawFPS(GetScreenWidth() - 110, 10);

  DrawRectangle(foodPosition.x, foodPosition.y, gridSize, gridSize, RED);
  snake.draw();

  switch (state) {
  case GameState::MENU:
    drawMenuScreen();
    break;
  case GameState::PLAYING:
    drawPlayingScreen();
    break;
  case GameState::GAME_OVER:
    drawGameOverScreen();
    break;
  }
}

void Game::run() {
  InitWindow(windowWidth, windowHeight, "Evil Snake");

  // int display = GetCurrentMonitor();
  // windowWidth = GetMonitorWidth(display);
  // windowHeight = GetMonitorHeight(display);

  // SetWindowSize(windowWidth, windowHeight);
  // ToggleFullscreen();

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();
    handleInput();
    update(deltaTime);

    BeginDrawing();
    draw();
    EndDrawing();
  }

  CloseWindow();
}
