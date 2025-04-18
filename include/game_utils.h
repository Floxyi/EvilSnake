#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include <string>

#include "game_mode.h"
#include "raylib.h"

namespace GameUtils
{
void applyApplicationIcon();
void takeScreenshot();
void openScreenshotsFolder();
Vector2 getRandomGridPosition();
Vector2 getRandomFoodPosition(const std::vector<Vector2> &snakePosition, const std::vector<Vector2> &wallPositions);
Vector2 getRandomWallPosition(const std::vector<Vector2> &snakePosition, const Vector2 &foodPosition);
std::string getFormattedGameTime(float startTime, float until);
std::string getFormattedGameMode(GameMode mode);
std::string getAssetPath();
}  // namespace GameUtils

#endif
