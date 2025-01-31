#include "../include/Utils.h"
#include "../include/Snake.h"
#include "raylib.h"

void Utils::takeScreenshot() {
  std::time_t now = std::time(nullptr);
  std::tm *localTime = std::localtime(&now);
  char timeBuffer[32];
  std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d_%H-%M-%S", localTime);
  std::string filename = "Screenshot_" + std::string(timeBuffer) + ".png";
  TakeScreenshot(filename.c_str());
}

Vector2 Utils::getRandomGridPosition(int gridSize, int windowWidth,
                                     int windowHeight) {
  int x = GetRandomValue(0, (windowWidth / gridSize) - 1) * gridSize;
  int y = GetRandomValue(0, (windowHeight / gridSize) - 1) * gridSize;
  return {(float)x, (float)y};
}

Vector2 Utils::getRandomFoodPosition(Snake &snake, int gridSize,
                                     int windowWidth, int windowHeight) {
  Vector2 position;
  do {
    position = getRandomGridPosition(gridSize, windowWidth, windowHeight);
  } while (snake.isOnSnake(position));
  return position;
}

Vector2 Utils::computeAlignedPosition(const char *text, float fontSize,
                                      HorizontalAlignment horizontalAlignment,
                                      VerticalAlignment verticalAlignment,
                                      float padding, int windowWidth,
                                      int windowHeight) {
  Vector2 position = {0, 0};
  float textWidth = MeasureText(text, fontSize);

  switch (horizontalAlignment) {
  case HorizontalAlignment::RIGHT:
    position.x = windowWidth - textWidth - padding;
    break;
  case HorizontalAlignment::CENTER:
    position.x = (windowWidth - textWidth) / 2;
    break;
  case HorizontalAlignment::LEFT:
    position.x = padding;
    break;
  }

  switch (verticalAlignment) {
  case VerticalAlignment::BOTTOM:
    position.y = windowHeight - fontSize - padding;
    break;
  case VerticalAlignment::CENTER:
    position.y = (windowHeight - fontSize) / 2 + padding;
    break;
  case VerticalAlignment::TOP:
    position.y = padding;
    break;
  }

  return position;
}

void Utils::drawAlignedText(const char *text, float fontSize, Color color,
                            VerticalAlignment verticalAlignment,
                            HorizontalAlignment horizontalAlignment,
                            float padding, int windowWidth, int windowHeight) {
  Vector2 position = computeAlignedPosition(text, fontSize, horizontalAlignment,
                                            verticalAlignment, padding,
                                            windowWidth, windowHeight);
  DrawText(text, position.x, position.y, fontSize, color);
}
