#include "../include/text_utils.h"

#include "../include/constants.h"
#include "../include/font_manager.h"

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

}  // namespace

void TextUtils::drawAlignedText(const char *text, int fontId, float fontSize, Color color,
    VerticalAlignment verticalAlignment, HorizontalAlignment horizontalAlignment, float padding)
{
    Font font = FontManager::getInstance().getFont(fontId);
    Vector2 textSize = MeasureTextEx(font, text, fontSize, 2);

    Vector2 position = {
        computeHorizontalPosition(horizontalAlignment, textSize.x, padding),
        computeVerticalPosition(verticalAlignment, textSize.y, padding),
    };

    DrawTextEx(font, text, position, fontSize, 2, color);
}
