#include "../include/Utils.h"
#include "../include/Position.h"
#include "../include/Snake.h"
#include "raylib.h"

Position Utils::getRandomGridPosition(int gridSize, int windowWidth,
                                      int windowHeight) {
  int x = GetRandomValue(0, (windowWidth / gridSize) - 1) * gridSize;
  int y = GetRandomValue(0, (windowHeight / gridSize) - 1) * gridSize;
  return {x, y};
}

Position Utils::getRandomFoodPosition(Snake &snake, int gridSize,
                                      int windowWidth, int windowHeight) {
  Position position;
  do {
    position = getRandomGridPosition(gridSize, windowWidth, windowHeight);
  } while (snake.isOnSnake(position));
  return position;
}

Position Utils::computeAlignedPosition(const char *text, float fontSize,
                                       HorizontalAlignment horizontalAlignment,
                                       VerticalAlignment verticalAlignment,
                                       float padding, int windowWidth,
                                       int windowHeight) {
  Position position = {0, 0};
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
  Position position = computeAlignedPosition(
      text, fontSize, horizontalAlignment, verticalAlignment, padding,
      windowWidth, windowHeight);
  DrawText(text, position.x, position.y, fontSize, color);
}
