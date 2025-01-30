#include "raylib.h"
#include <string>
#include <vector>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 450;

constexpr int MAX_SNAKE_LENGTH = 100;
constexpr int GRID_SIZE = 40;
constexpr float SNAKE_MOVE_INTERVAL = 0.15f;

struct Position {
  int x;
  int y;
};

enum GameState { GAME_STATE_MENU, GAME_STATE_PLAYING, GAME_STATE_GAME_OVER };
enum SnakeDirection { UP, DOWN, LEFT, RIGHT };

struct Snake {
  std::vector<Position> body;
  SnakeDirection snakeDirection;
  int speed;
};

struct Game {
  GameState gameState;
  Position foodPosition;
  Snake snake;
  int score;
  float timeSinceLastMove;
};

enum WindowAlignmentY {
  WINDOW_ALIGN_Y_TOP,
  WINDOW_ALIGN_Y_CENTER,
  WINDOW_ALIGN_Y_BOTTOM
};

enum WindowAlignmentX {
  WINDOW_ALIGN_X_LEFT,
  WINDOW_ALIGN_X_CENTER,
  WINDOW_ALIGN_X_RIGHT
};

Game GAME;

Position getRandomGridPosition() {
  int x = GetRandomValue(0, WINDOW_WIDTH / GRID_SIZE - 1) * GRID_SIZE;
  int y = GetRandomValue(0, WINDOW_HEIGHT / GRID_SIZE - 1) * GRID_SIZE;
  return {x, y};
}

Position getAlignedPosition(const char *text, float fontSize,
                            WindowAlignmentX windowXAlignment,
                            WindowAlignmentY windowYAlignment, float padding) {
  Position position = {0, 0};
  float width = MeasureText(text, fontSize);

  switch (windowXAlignment) {
  case WINDOW_ALIGN_X_RIGHT:
    position.x = WINDOW_WIDTH - padding - width;
    break;
  case WINDOW_ALIGN_X_CENTER:
    position.x = (WINDOW_WIDTH - width) / 2;
    break;
  case WINDOW_ALIGN_X_LEFT:
    position.x = padding;
    break;
  }

  switch (windowYAlignment) {
  case WINDOW_ALIGN_Y_BOTTOM:
    position.y = WINDOW_HEIGHT - padding - fontSize;
    break;
  case WINDOW_ALIGN_Y_CENTER:
    position.y = (WINDOW_HEIGHT - fontSize) / 2 + padding;
    break;
  case WINDOW_ALIGN_Y_TOP:
    position.y = padding;
    break;
  }

  return position;
}

void DrawAlignedText(const char *text, float fontSize, Color color,
                     WindowAlignmentY windowYAlignment = WINDOW_ALIGN_Y_CENTER,
                     WindowAlignmentX windowXAlignment = WINDOW_ALIGN_X_CENTER,
                     float padding = 0) {
  Position position = getAlignedPosition(text, fontSize, windowXAlignment,
                                         windowYAlignment, padding);
  DrawText(text, position.x, position.y, fontSize, color);
}

void DrawGrid(int gridSize, Color color) {
  for (int x = 0; x < WINDOW_WIDTH; x += gridSize) {
    DrawLine(x, 0, x, WINDOW_HEIGHT, color);
  }
  for (int y = 0; y < WINDOW_HEIGHT; y += gridSize) {
    DrawLine(0, y, WINDOW_WIDTH, y, color);
  }
}

Game initializeGame() {
  Game game = {};
  game.gameState = GAME_STATE_MENU;
  game.snake.body = {getRandomGridPosition()};
  game.foodPosition = getRandomGridPosition();
  game.score = 0;
  game.timeSinceLastMove = 0.0f;
  game.snake.snakeDirection = UP;
  return game;
}

void handleFoodCollision(Position &head) {
  if (head.x == GAME.foodPosition.x && head.y == GAME.foodPosition.y) {
    GAME.score++;
    GAME.foodPosition = getRandomGridPosition();
  } else {
    GAME.snake.body.pop_back();
  }
}

void handleSelfCollision(Position &head) {
  for (Position bodyPosition : GAME.snake.body) {
    if (head.x == bodyPosition.x && head.y == bodyPosition.y) {
      GAME.gameState = GAME_STATE_GAME_OVER;
    }
  }
}

void handleSnakeMovement(float deltaTime) {
  GAME.timeSinceLastMove += deltaTime;

  Position newHead = GAME.snake.body.front();

  if (GAME.timeSinceLastMove >= SNAKE_MOVE_INTERVAL) {
    switch (GAME.snake.snakeDirection) {
    case UP:
      newHead.y -= GRID_SIZE;
      break;
    case DOWN:
      newHead.y += GRID_SIZE;
      break;
    case LEFT:
      newHead.x -= GRID_SIZE;
      break;
    case RIGHT:
      newHead.x += GRID_SIZE;
      break;
    }

    newHead.x = (newHead.x + WINDOW_WIDTH) % WINDOW_WIDTH;
    newHead.y = (newHead.y + WINDOW_HEIGHT) % WINDOW_HEIGHT;

    handleSelfCollision(newHead);

    GAME.snake.body.insert(GAME.snake.body.begin(), newHead);

    handleFoodCollision(newHead);

    GAME.timeSinceLastMove = 0.0f;
  }
}

void handleInput() {
  if (IsKeyPressed(KEY_UP)) {
    GAME.snake.snakeDirection = UP;
  }
  if (IsKeyPressed(KEY_DOWN)) {
    GAME.snake.snakeDirection = DOWN;
  }
  if (IsKeyPressed(KEY_LEFT)) {
    GAME.snake.snakeDirection = LEFT;
  }
  if (IsKeyPressed(KEY_RIGHT)) {
    GAME.snake.snakeDirection = RIGHT;
  }
}

void handleGameState() {
  if (GAME.gameState == GAME_STATE_MENU && IsKeyPressed(KEY_UP)) {
    GAME.gameState = GAME_STATE_PLAYING;
  }

  if (GAME.gameState == GAME_STATE_PLAYING && IsKeyPressed(KEY_SPACE)) {
    GAME = initializeGame();
    GAME.gameState = GAME_STATE_MENU;
  }

  if (GAME.gameState == GAME_STATE_GAME_OVER && IsKeyPressed(KEY_SPACE)) {
    GAME = initializeGame();
    GAME.gameState = GAME_STATE_MENU;
  }
}

void drawGameOverScreen() {
  DrawAlignedText("GAME OVER", 40, DARKGRAY, WINDOW_ALIGN_Y_CENTER,
                  WINDOW_ALIGN_X_CENTER, -100);
  DrawAlignedText((std::string("Score: ") + std::to_string(GAME.score)).c_str(),
                  20, DARKGRAY, WINDOW_ALIGN_Y_CENTER, WINDOW_ALIGN_X_CENTER,
                  -50);
  DrawAlignedText("Press the [SPACE] key to get back to the menu", 20, DARKGRAY,
                  WINDOW_ALIGN_Y_CENTER, WINDOW_ALIGN_X_CENTER, 50);
}

void drawMenuScreen() {
  DrawAlignedText("Welcome to EvilSnake!", 40, DARKGRAY, WINDOW_ALIGN_Y_TOP,
                  WINDOW_ALIGN_X_CENTER, 50);
  DrawAlignedText("Press the [UP ARROW] key to start the game", 20, DARKGRAY,
                  WINDOW_ALIGN_Y_TOP, WINDOW_ALIGN_X_CENTER, 120);
  DrawAlignedText("v1.0", 20, DARKGRAY, WINDOW_ALIGN_Y_BOTTOM,
                  WINDOW_ALIGN_X_RIGHT, 10);
  DrawAlignedText("Made by Florian", 20, DARKGRAY, WINDOW_ALIGN_Y_BOTTOM,
                  WINDOW_ALIGN_X_LEFT, 10);
}

void drawPlayingScreen() {
  DrawAlignedText((std::string("Score: ") + std::to_string(GAME.score)).c_str(),
                  20, DARKGRAY, WINDOW_ALIGN_Y_TOP, WINDOW_ALIGN_X_LEFT, 10);
  DrawAlignedText("Press the [SPACE] key to get back to the menu", 20, DARKGRAY,
                  WINDOW_ALIGN_Y_BOTTOM, WINDOW_ALIGN_X_CENTER, 10);
}

int main() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Evil Snake");

  int display = GetCurrentMonitor();
  WINDOW_WIDTH = GetMonitorWidth(display);
  WINDOW_HEIGHT = GetMonitorHeight(display);

  SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  ToggleFullscreen();

  GAME = initializeGame();

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();

    handleInput();
    handleGameState();

    if (GAME.gameState == GAME_STATE_PLAYING) {
      handleSnakeMovement(deltaTime);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawGrid(GRID_SIZE, LIGHTGRAY);
    DrawFPS(GetScreenWidth() - 110, 10);

    switch (GAME.gameState) {
    case GAME_STATE_MENU:
      drawMenuScreen();
      break;
    case GAME_STATE_PLAYING:
      drawPlayingScreen();
      break;
    case GAME_STATE_GAME_OVER:
      drawGameOverScreen();
      break;
    }

    DrawRectangle(GAME.foodPosition.x, GAME.foodPosition.y, GRID_SIZE,
                  GRID_SIZE, RED);

    for (Position position : GAME.snake.body) {
      DrawRectangle(position.x, position.y, GRID_SIZE, GRID_SIZE, DARKGREEN);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
