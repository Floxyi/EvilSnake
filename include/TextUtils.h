#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include "raylib.h"

enum class VerticalAlignment { TOP, CENTER, BOTTOM };
enum class HorizontalAlignment { LEFT, CENTER, RIGHT };

namespace TextUtils {

void drawAlignedText(const char *text, int fontId, float fontSize, Color color,
                     VerticalAlignment verticalAlignment,
                     HorizontalAlignment horizontalAlignment, float padding);

} // namespace TextUtils

#endif
