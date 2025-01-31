#include "../include/Game.h"
#include "../include/Constants.h"
#include "../include/Utils.h"
#include "raylib.h"

Game::Game(int width, int height, int gridSize)
    : windowWidth(width), windowHeight(height), gridSize(gridSize),
      state(GameState::MENU), score(0), timeSinceLastMove(0.0f),
      snake(gridSize), startTime(0.0f) {
  foodPosition =
      Utils::getRandomGridPosition(gridSize, windowWidth, windowHeight);
}

void Game::reset() {
  this->score = 0;
  this->snake.reset();
  state = GameState::MENU;
  startTime = 0.0f;
}

bool Game::isGameFinished() const {
  return score >= Constants::GRID_Y_AMOUNT * Constants::WINDOW_WIDTH /
                      Constants::GRID_SIZE;
}

void Game::handleInput() {
  if (IsKeyPressed(KEY_S)) {
    Utils::takeScreenshot();
  }

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
  if (isGameFinished()) {
    state = GameState::FINISHED;
  }

  if (state == GameState::PLAYING) {
    if (startTime == 0.0f) {
      startTime = GetTime();
    }

    timeSinceLastMove += deltaTime;

    if (timeSinceLastMove >= Constants::SNAKE_SPEED) {
      timeSinceLastMove = 0.0f;

      if (snake.move(foodPosition)) {
        score++;
        foodPosition = Utils::getRandomFoodPosition(snake, gridSize,
                                                    windowWidth, windowHeight);
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

void Game::drawGameFinishedScreen() {
  Utils::drawAlignedText("YOU WON, CONGRATULATIONS!", 40, DARKGRAY,
                         VerticalAlignment::CENTER, HorizontalAlignment::CENTER,
                         -100, windowWidth, windowHeight);
  Utils::drawAlignedText(
      (std::string("Score: ") + std::to_string(score)).c_str(), 20, DARKGRAY,
      VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50, windowWidth,
      windowHeight);
  Utils::drawAlignedText("[SPACE] - Back to main menu", 20, DARKGRAY,
                         VerticalAlignment::CENTER, HorizontalAlignment::CENTER,
                         50, windowWidth, windowHeight);
}

void Game::drawMenuScreen() {
  Utils::drawAlignedText("Welcome to EvilSnake!", 40, DARKGRAY,
                         VerticalAlignment::TOP, HorizontalAlignment::CENTER,
                         50, windowWidth, windowHeight);
  Utils::drawAlignedText(
      "Press the [ARROW KEYS] key to start and play the game", 20, DARKGRAY,
      VerticalAlignment::TOP, HorizontalAlignment::CENTER, 120, windowWidth,
      windowHeight);
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
  float elapsedTime =
      state == GameState::PLAYING ? GetTime() - startTime : 0.0f;

  int minutes = static_cast<int>(elapsedTime) / 60;
  int seconds = static_cast<int>(elapsedTime) % 60;
  int milliseconds =
      static_cast<int>((elapsedTime - static_cast<int>(elapsedTime)) * 100);

  std::string timeString =
      (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
      (seconds < 10 ? "0" : "") + std::to_string(seconds) + ":" +
      (milliseconds < 10 ? "0" : "") + std::to_string(milliseconds);

  Utils::drawAlignedText(
      (std::string("Score: ") + std::to_string(score)).c_str(), 20, DARKGRAY,
      VerticalAlignment::TOP, HorizontalAlignment::LEFT, 10, windowWidth,
      windowHeight);
  Utils::drawAlignedText(("Time: " + timeString).c_str(), 20, DARKGRAY,
                         VerticalAlignment::TOP, HorizontalAlignment::RIGHT, 10,
                         windowWidth, windowHeight);
  Utils::drawAlignedText("[SPACE] - Quit to main menu", 20, DARKGRAY,
                         VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER,
                         10, windowWidth, windowHeight);
}

void Game::draw() {
  ClearBackground(Constants::BACKGROUND_COLOR);
  drawGrid(gridSize, LIGHTGRAY);

  DrawRectangle(foodPosition.x, foodPosition.y, gridSize, gridSize, RED);
  snake.draw();

  switch (state) {
  case GameState::MENU:
    drawMenuScreen();
    break;
  case GameState::PLAYING:
    drawPlayingScreen();
    break;
  case GameState::FINISHED:
    drawGameFinishedScreen();
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
