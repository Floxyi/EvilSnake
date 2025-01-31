#include "../include/Game.h"
#include "../include/Constants.h"
#include "../include/FontManager.h"
#include "../include/SoundManager.h"
#include "../include/TextUtils.h"
#include "raylib.h"

Game::Game(int width, int height, int gridSize)
    : windowWidth(width), windowHeight(height), gridSize(gridSize),
      state(GameState::MENU), score(0), timeSinceLastMove(0.0f),
      snake(gridSize), startTime(0.0f) {
  foodPosition = getRandomGridPosition(gridSize, windowWidth, windowHeight);
}

void Game::takeScreenshot() const {
  std::time_t now = std::time(nullptr);
  std::tm *localTime = std::localtime(&now);
  char timeBuffer[32];
  std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d_%H-%M-%S", localTime);
  std::string filename = "Screenshot_" + std::string(timeBuffer) + ".png";
  TakeScreenshot(filename.c_str());
}

Vector2 Game::getRandomGridPosition(int gridSize, int windowWidth,
                                    int windowHeight) const {
  int x = GetRandomValue(0, (windowWidth / gridSize) - 1) * gridSize;
  int y = GetRandomValue(0, (windowHeight / gridSize) - 1) * gridSize;
  return {(float)x, (float)y};
}

Vector2 Game::getRandomFoodPosition(Snake &snake, int gridSize, int windowWidth,
                                    int windowHeight) const {
  Vector2 position;
  do {
    position = getRandomGridPosition(gridSize, windowWidth, windowHeight);
  } while (snake.isOnSnake(position));
  return position;
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
    takeScreenshot();
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
        SoundManager::getInstance().play(SoundManager::SOUND_START);
        state = GameState::PLAYING;
      }
      snake.setDirection(Direction::UP);
    }
    if (IsKeyPressed(KEY_DOWN)) {
      if (state == GameState::MENU) {
        SoundManager::getInstance().play(SoundManager::SOUND_START);
        state = GameState::PLAYING;
      }
      snake.setDirection(Direction::DOWN);
    }
    if (IsKeyPressed(KEY_LEFT)) {
      if (state == GameState::MENU) {
        SoundManager::getInstance().play(SoundManager::SOUND_START);
        state = GameState::PLAYING;
      }
      snake.setDirection(Direction::LEFT);
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      if (state == GameState::MENU) {
        SoundManager::getInstance().play(SoundManager::SOUND_START);
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
        SoundManager::getInstance().play(SoundManager::SOUND_EAT);
        score++;
        foodPosition =
            getRandomFoodPosition(snake, gridSize, windowWidth, windowHeight);
      }

      if (snake.hasCollided()) {
        SoundManager::getInstance().play(SoundManager::SOUND_EXPLOSION);
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
  TextUtils::drawAlignedText("GAME OVER", FontManager::FONT_MAIN, 60, DARKGRAY,
                             VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -100);
  TextUtils::drawAlignedText(
      (std::string("Score: ") + std::to_string(score)).c_str(),
      FontManager::FONT_MAIN, 30, DARKGRAY, VerticalAlignment::CENTER,
      HorizontalAlignment::CENTER, -50);
  TextUtils::drawAlignedText(
      "Press the [SPACE] key to get back to the menu", FontManager::FONT_MAIN,
      30, DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, 50);
}

void Game::drawGameFinishedScreen() {
  TextUtils::drawAlignedText(
      "YOU WON, CONGRATULATIONS!", FontManager::FONT_MAIN, 60, DARKGRAY,
      VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -100);
  TextUtils::drawAlignedText(
      (std::string("Score: ") + std::to_string(score)).c_str(),
      FontManager::FONT_MAIN, 30, DARKGRAY, VerticalAlignment::CENTER,
      HorizontalAlignment::CENTER, -50);
  TextUtils::drawAlignedText(
      "[SPACE] - Back to main menu", FontManager::FONT_MAIN, 30, DARKGRAY,
      VerticalAlignment::CENTER, HorizontalAlignment::CENTER, 50);
}

void Game::drawMenuScreen() {
  TextUtils::drawAlignedText("EvilSnake", FontManager::FONT_TITLE, 80, DARKGRAY,
                             VerticalAlignment::TOP,
                             HorizontalAlignment::CENTER, 60);
  TextUtils::drawAlignedText(
      "Press the [ARROW KEYS] key to start and play the game",
      FontManager::FONT_MAIN, 25, DARKGRAY, VerticalAlignment::TOP,
      HorizontalAlignment::CENTER, 180);
  TextUtils::drawAlignedText("Made by Florian", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::LEFT, 10);
  TextUtils::drawAlignedText("[ESC] - Quit", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 10);
  TextUtils::drawAlignedText("v1.0", FontManager::FONT_MAIN, 20, DARKGRAY,
                             VerticalAlignment::BOTTOM,
                             HorizontalAlignment::RIGHT, 10);
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

  TextUtils::drawAlignedText(
      (std::string("Score: ") + std::to_string(score)).c_str(),
      FontManager::FONT_MAIN, 30, DARKGRAY, VerticalAlignment::TOP,
      HorizontalAlignment::RIGHT, 10);
  TextUtils::drawAlignedText(
      ("Time: " + timeString).c_str(), FontManager::FONT_MAIN, 30, DARKGRAY,
      VerticalAlignment::TOP, HorizontalAlignment::LEFT, 10);
  TextUtils::drawAlignedText(
      "[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 20, DARKGRAY,
      VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER, 10);
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
  Image icon = LoadImage("assets/textures/EvilSnake.png");
  SetWindowIcon(icon);
  UnloadImage(icon);

  FontManager::getInstance().initFonts();
  SoundManager::getInstance().initSounds();

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
