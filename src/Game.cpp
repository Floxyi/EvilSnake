#include "../include/Game.h"
#include "../include/Constants.h"
#include "../include/FontManager.h"
#include "../include/SoundManager.h"
#include "../include/TextUtils.h"
#include "raylib.h"

Game::Game()
    : state(GameState::MENU), mode(GameMode::NORMAL), score(0),
      timeSinceLastMove(0.0f), timeSinceLastEventCheck(0.0f), startTime(0.0f),
      endTime(0.0f), snake(getRandomGridPosition()), wallPositions{} {
  foodPosition = getRandomFoodPosition(snake);
}

void Game::takeScreenshot() const {
  std::time_t now = std::time(nullptr);
  std::tm *localTime = std::localtime(&now);
  char timeBuffer[32];
  std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d_%H-%M-%S", localTime);
  std::string filename = "Screenshot_" + std::string(timeBuffer) + ".png";
  TakeScreenshot(filename.c_str());
}

Vector2 Game::getRandomGridPosition() const {
  int x =
      GetRandomValue(0, (Constants::WINDOW_WIDTH / Constants::GRID_SIZE) - 1) *
      Constants::GRID_SIZE;
  int y =
      GetRandomValue(0, (Constants::WINDOW_HEIGHT / Constants::GRID_SIZE) - 1) *
      Constants::GRID_SIZE;
  return {(float)x, (float)y};
}

Vector2 Game::getRandomFoodPosition(Snake &snake) const {
  Vector2 position;
  bool isOnWall = false;
  do {
    position = getRandomGridPosition();
    for (const Vector2 &wallPosition : wallPositions) {
      if (position.x == wallPosition.x && position.y == wallPosition.y) {
        isOnWall = true;
      }
    }
  } while (snake.isOnSnake(position) && isOnWall);
  return position;
}

Vector2 Game::getRandomWallPosition(Snake &snake) const {
  Vector2 position;
  bool isOnFood = false;
  do {
    position = getRandomGridPosition();
    if (position.x == foodPosition.x && position.y == foodPosition.y) {
      isOnFood = true;
    }
  } while (snake.isOnSnake(position) && isOnFood);
  return position;
}

void Game::reset() {
  score = 0;
  startTime = 0.0f;
  endTime = 0.0f;
  state = GameState::MENU;
  mode = GameMode::NORMAL;
  wallPositions = {};

  snake.resetToPosition(getRandomGridPosition());
  foodPosition = getRandomWallPosition(snake);
}

bool Game::isGameFinished() const {
  return score >= Constants::GRID_Y_AMOUNT * Constants::WINDOW_WIDTH /
                      Constants::GRID_SIZE;
}

void Game::handleInput() {
  if (IsKeyPressed(KEY_E)) {
    takeScreenshot();
  }

  if (state == GameState::PLAYING || state == GameState::FINISHED ||
      state == GameState::GAME_OVER || state == GameState::PAUSED) {
    if (IsKeyPressed(KEY_SPACE)) {
      reset();
    }
  }

  if (state == GameState::PLAYING) {
    if (IsKeyPressed(KEY_P)) {
      endTime = GetTime();
      state = GameState::PAUSED;
    }
  }

  if (state == GameState::PAUSED) {
    if (IsKeyPressed(KEY_O)) {
      endTime = 0.0f;
      state = GameState::PLAYING;
    }
  }

  if (state == GameState::PLAYING || state == GameState::MENU) {
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
      handleDirectionChange(Direction::UP);
    }
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
      handleDirectionChange(Direction::DOWN);
    }
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
      handleDirectionChange(Direction::LEFT);
    }
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
      handleDirectionChange(Direction::RIGHT);
    }
  }
}

void Game::handleDirectionChange(Direction dir) {
  if (state == GameState::MENU) {
    SoundManager::getInstance().play(SoundManager::SOUND_START);
    startTime = GetTime();
    state = GameState::PLAYING;
  }
  snake.setDirection(dir);
}

void Game::changeGameMode() {
  int random = GetRandomValue(0, 2);

  if (random == 0 && mode != GameMode::NORMAL) {
    mode = GameMode::NORMAL;
    SoundManager::getInstance().play(SoundManager::SOUND_START);
    snake.speed = Constants::DEFAULT_SNAKE_SPEED;
    wallPositions = {};
  }

  if (random == 1 && mode != GameMode::FAST) {
    mode = GameMode::FAST;
    SoundManager::getInstance().play(SoundManager::SOUND_START);
    snake.speed = Constants::FAST_SNAKE_SPEED;
    wallPositions = {};
  }

  if (random == 2 && mode != GameMode::WALLS) {
    mode = GameMode::WALLS;
    SoundManager::getInstance().play(SoundManager::SOUND_START);
    snake.speed = Constants::DEFAULT_SNAKE_SPEED;
    wallPositions = {};
    for (int i = 0; i < Constants::WALL_AMOUNT; i++) {
      wallPositions.push_back(getRandomGridPosition());
    }
  }
}

void Game::update() {
  if (isGameFinished()) {
    state = GameState::FINISHED;
  }

  if (state != GameState::PLAYING) {
    return;
  }

  timeSinceLastMove += GetFrameTime();
  timeSinceLastEventCheck += GetFrameTime();

  if (timeSinceLastEventCheck >= Constants::EVENT_PROBABILITY) {
    timeSinceLastEventCheck = 0.0f;
    changeGameMode();
  }

  if (timeSinceLastMove >= snake.speed) {
    timeSinceLastMove = 0.0f;

    if (snake.moveAndCheckForFood(foodPosition)) {
      SoundManager::getInstance().play(SoundManager::SOUND_EAT);
      score++;
      foodPosition = getRandomFoodPosition(snake);
    }

    if (snake.hasCollided(wallPositions)) {
      SoundManager::getInstance().play(SoundManager::SOUND_EXPLOSION);
      endTime = GetTime();
      state = GameState::GAME_OVER;
    }
  }
}

void Game::drawGrid(Color color) {
  for (int x = 0; x < Constants::WINDOW_WIDTH; x += Constants::GRID_SIZE) {
    DrawLine(x, 0, x, Constants::WINDOW_HEIGHT, color);
  }
  for (int y = 0; y < Constants::WINDOW_HEIGHT; y += Constants::GRID_SIZE) {
    DrawLine(0, y, Constants::WINDOW_WIDTH, y, color);
  }
}

void Game::drawGameOverScreen() {
  std::string time = getFormattedGameTime(endTime);

  TextUtils::drawAlignedText("GAME OVER", FontManager::FONT_MAIN, 60, DARKGRAY,
                             VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -120);
  TextUtils::drawAlignedText(
      ("Score: " + std::to_string(score)).c_str(), FontManager::FONT_MAIN, 30,
      DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50);
  TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN,
                             30, DARKGRAY, VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -70);
  TextUtils::drawAlignedText(
      "[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 30, DARKGRAY,
      VerticalAlignment::CENTER, HorizontalAlignment::CENTER, 50);
}

void Game::drawGameFinishedScreen() {
  std::string time = getFormattedGameTime(endTime);

  TextUtils::drawAlignedText(
      "YOU WON, CONGRATULATIONS!", FontManager::FONT_MAIN, 60, DARKGRAY,
      VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -120);
  TextUtils::drawAlignedText(
      ("Score: " + std::to_string(score)).c_str(), FontManager::FONT_MAIN, 30,
      DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50);
  TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN,
                             30, DARKGRAY, VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -70);
  TextUtils::drawAlignedText(
      "[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 30, DARKGRAY,
      VerticalAlignment::CENTER, HorizontalAlignment::CENTER, 50);
}

void Game::drawMenuScreen() {
  TextUtils::drawAlignedText("EvilSnake", FontManager::FONT_TITLE, 80, DARKGRAY,
                             VerticalAlignment::TOP,
                             HorizontalAlignment::CENTER, 60);
  TextUtils::drawAlignedText(
      "Press the [ARROW KEYS / WASD] key to start and play the game",
      FontManager::FONT_MAIN, 25, DARKGRAY, VerticalAlignment::TOP,
      HorizontalAlignment::CENTER, 180);
  TextUtils::drawAlignedText("Made by Florian", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::LEFT, 10);
  TextUtils::drawAlignedText("[ESC] - Quit", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 10);
  TextUtils::drawAlignedText("[P/O] - Pause/Continue", FontManager::FONT_MAIN,
                             20, DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 30);
  TextUtils::drawAlignedText(
      "[Space] - Quit to main menu", FontManager::FONT_MAIN, 20, DARKGRAY,
      VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER, 50);
  TextUtils::drawAlignedText("[E] - Screenshot", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 70);
  TextUtils::drawAlignedText("v1.0", FontManager::FONT_MAIN, 20, DARKGRAY,
                             VerticalAlignment::BOTTOM,
                             HorizontalAlignment::RIGHT, 10);
}

std::string Game::getFormattedGameTime(float until) const {
  float elapsedTime = until - startTime;

  int minutes = elapsedTime / 60;
  int seconds = (int)(elapsedTime) % 60;
  int milliseconds = ((elapsedTime - static_cast<int>(elapsedTime)) * 100);

  std::string timeString =
      (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
      (seconds < 10 ? "0" : "") + std::to_string(seconds) + ":" +
      (milliseconds < 10 ? "0" : "") + std::to_string(milliseconds);

  return timeString;
}

std::string Game::getFormattedGameMode() const {
  std::string modeString;

  switch (mode) {
  case GameMode::NORMAL:
    modeString = "Normal";
    break;
  case GameMode::FAST:
    modeString = "Fast";
    break;
  case GameMode::WALLS:
    modeString = "Walls";
    break;
  }

  return modeString;
}

void Game::drawPlayingScreen() {
  std::string time = getFormattedGameTime(GetTime());
  std::string mode = getFormattedGameMode();

  TextUtils::drawAlignedText(
      ("Score: " + std::to_string(score)).c_str(), FontManager::FONT_MAIN, 30,
      DARKGRAY, VerticalAlignment::TOP, HorizontalAlignment::RIGHT, 10);
  TextUtils::drawAlignedText(("Mode: " + mode).c_str(), FontManager::FONT_MAIN,
                             30, DARKGRAY, VerticalAlignment::TOP,
                             HorizontalAlignment::CENTER, 10);
  TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN,
                             30, DARKGRAY, VerticalAlignment::TOP,
                             HorizontalAlignment::LEFT, 10);
  TextUtils::drawAlignedText(
      "[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 20, DARKGRAY,
      VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER, 10);
  TextUtils::drawAlignedText("[P] - Pause", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 30);
}

void Game::drawPauseScreen() {
  std::string time = getFormattedGameTime(endTime);

  TextUtils::drawAlignedText("Pause", FontManager::FONT_MAIN, 60, DARKGRAY,
                             VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -120);
  TextUtils::drawAlignedText(
      ("Score: " + std::to_string(score)).c_str(), FontManager::FONT_MAIN, 30,
      DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50);
  TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN,
                             30, DARKGRAY, VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -70);
  TextUtils::drawAlignedText(
      "[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 20, DARKGRAY,
      VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER, 10);
  TextUtils::drawAlignedText("[O] - Continue", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 30);
}

void Game::draw() {
  ClearBackground(Constants::BACKGROUND_COLOR);
  drawGrid(LIGHTGRAY);

  DrawRectangle(foodPosition.x, foodPosition.y, Constants::GRID_SIZE,
                Constants::GRID_SIZE, RED);
  snake.draw();
  for (const Vector2 &wallPosition : wallPositions) {
    DrawRectangle(wallPosition.x, wallPosition.y, Constants::GRID_SIZE,
                  Constants::GRID_SIZE, BLACK);
  }

  switch (state) {
  case GameState::MENU:
    drawMenuScreen();
    break;
  case GameState::PLAYING:
    drawPlayingScreen();
    break;
  case GameState::PAUSED:
    drawPauseScreen();
    break;
  case GameState::FINISHED:
    drawGameFinishedScreen();
    break;
  case GameState::GAME_OVER:
    drawGameOverScreen();
    break;
  }
}

void Game::init() {
  InitWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Evil Snake");
  Image icon = LoadImage("assets/textures/EvilSnake.png");
  SetWindowIcon(icon);
  UnloadImage(icon);

  FontManager::getInstance().initFonts();
  SoundManager::getInstance().initSounds();
}

void Game::run() {
  init();

  while (!WindowShouldClose()) {
    handleInput();
    update();

    BeginDrawing();
    draw();
    EndDrawing();
  }

  CloseWindow();
}
