#ifndef UTILS_H
#define UTILS_H

#include "Position.h"
#include "raylib.h"

enum class VerticalAlignment { TOP, CENTER, BOTTOM };
enum class HorizontalAlignment { LEFT, CENTER, RIGHT };

class Utils {
public:
  static Position getRandomGridPosition(int gridSize, int windowWidth,
                                        int windowHeight);

  static void drawAlignedText(const char *text, float fontSize, Color color,
                              VerticalAlignment verticalAlignment,
                              HorizontalAlignment horizontalAlignment,
                              float padding, int windowWidth, int windowHeight);

private:
  static Position
  computeAlignedPosition(const char *text, float fontSize,
                         HorizontalAlignment horizontalAlignment,
                         VerticalAlignment verticalAlignment, float padding,
                         int windowWidth, int windowHeight);
};

#endif
