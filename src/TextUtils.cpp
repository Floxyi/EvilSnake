#include "../include/TextUtils.h"
#include "../include/Constants.h"
#include "../include/FontManager.h"

Vector2
TextUtils::computeAlignedPosition(const char *text, Font font, float fontSize,
                                  HorizontalAlignment horizontalAlignment,
                                  VerticalAlignment verticalAlignment,
                                  float padding) {
  Vector2 position = {0, 0};
  float textWidth = MeasureTextEx(font, text, fontSize, 2).x;

  switch (horizontalAlignment) {
  case HorizontalAlignment::RIGHT:
    position.x = Constants::WINDOW_WIDTH - textWidth - padding;
    break;
  case HorizontalAlignment::CENTER:
    position.x = (Constants::WINDOW_WIDTH - textWidth) / 2;
    break;
  case HorizontalAlignment::LEFT:
    position.x = padding;
    break;
  }

  switch (verticalAlignment) {
  case VerticalAlignment::BOTTOM:
    position.y = Constants::WINDOW_HEIGHT - fontSize - padding;
    break;
  case VerticalAlignment::CENTER:
    position.y = (Constants::WINDOW_HEIGHT - fontSize) / 2 + padding;
    break;
  case VerticalAlignment::TOP:
    position.y = padding;
    break;
  }

  return position;
}

void TextUtils::drawAlignedText(const char *text, int fontId, float fontSize,
                                Color color,
                                VerticalAlignment verticalAlignment,
                                HorizontalAlignment horizontalAlignment,
                                float padding) {
  Font font = FontManager::getInstance().getFont(fontId);
  Vector2 position = computeAlignedPosition(
      text, font, fontSize, horizontalAlignment, verticalAlignment, padding);
  DrawTextEx(font, text, position, fontSize, 2, color);
}
