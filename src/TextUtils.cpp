#include "../include/TextUtils.h"

#include "../include/Constants.h"
#include "../include/FontManager.h"

namespace
{

float computeHorizontalPosition(HorizontalAlignment alignment, float textWidth, float padding)
{
    switch (alignment) {
        case HorizontalAlignment::RIGHT:
            return Constants::WINDOW_WIDTH - textWidth - padding;
        case HorizontalAlignment::CENTER:
            return (Constants::WINDOW_WIDTH - textWidth) / 2;
        case HorizontalAlignment::LEFT:
            return padding;
        default:
            return padding;
    }
}

float computeVerticalPosition(VerticalAlignment alignment, float fontSize, float padding)
{
    switch (alignment) {
        case VerticalAlignment::BOTTOM:
            return Constants::WINDOW_HEIGHT - fontSize - padding;
        case VerticalAlignment::CENTER:
            return (Constants::WINDOW_HEIGHT - fontSize) / 2 + padding;
        case VerticalAlignment::TOP:
            return padding;
        default:
            return padding;
    }
}

Vector2 computeAlignedPosition(const char *text, Font font, float fontSize, HorizontalAlignment horizontalAlignment,
    VerticalAlignment verticalAlignment, float padding)
{
    Vector2 position = {0, 0};

    float textWidth = MeasureTextEx(font, text, fontSize, 2).x;

    position.x = computeHorizontalPosition(horizontalAlignment, textWidth, padding);
    position.y = computeVerticalPosition(verticalAlignment, fontSize, padding);

    return position;
}

}  // namespace

void TextUtils::drawAlignedText(const char *text, int fontId, float fontSize, Color color,
    VerticalAlignment verticalAlignment, HorizontalAlignment horizontalAlignment, float padding)
{
    Font font = FontManager::getInstance().getFont(fontId);
    Vector2 position = computeAlignedPosition(text, font, fontSize, horizontalAlignment, verticalAlignment, padding);
    DrawTextEx(font, text, position, fontSize, 2, color);
}
