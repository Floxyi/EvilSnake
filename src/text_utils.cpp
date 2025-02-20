/**
 * @file text_utils.cpp
 * @brief Implementation of text rendering utilities for the Evil Snake game
 *
 * This file provides functions for rendering text with alignment options.
 * It includes horizontal and vertical positioning logic to place text
 * correctly on the game window.
 */

#include "../include/text_utils.h"

#include "../include/constants.h"
#include "../include/font_manager.h"

namespace
{
/**
 * @brief Computes the horizontal position for text rendering.
 *
 * @param alignment The desired horizontal alignment.
 * @param textWidth The width of the text to be drawn.
 * @param padding Additional padding from the aligned edge.
 * @return float The computed x-coordinate for text positioning.
 */
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

/**
 * @brief Computes the vertical position for text rendering.
 *
 * @param alignment The desired vertical alignment.
 * @param fontSize The font size of the text.
 * @param padding Additional padding from the aligned edge.
 * @return float The computed y-coordinate for text positioning.
 */
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

/**
 * @brief Draws text with alignment options.
 *
 * @param text The text string to render.
 * @param fontId The ID of the font to use.
 * @param fontSize The font size to render the text.
 * @param color The color of the text.
 * @param verticalAlignment The vertical alignment of the text.
 * @param horizontalAlignment The horizontal alignment of the text.
 * @param padding Additional padding from the aligned edge.
 */
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
