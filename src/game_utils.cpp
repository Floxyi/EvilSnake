#include "../include/game_utils.h"

#include <raylib.h>

#include <ctime>
#include <format>

#include "../include/constants.h"
#include "../include/game_mode.h"

namespace
{

bool isPositionOnSnake(Vector2 position, const std::vector<Vector2> &snakePosition)
{
    return std::find_if(snakePosition.begin(), snakePosition.end(), [&](const Vector2 &bodyPart) {
        return bodyPart.x == position.x && bodyPart.y == position.y;
    }) != snakePosition.end();
}

}  // namespace

void GameUtils::applyApplicationIcon()
{
    Image icon = LoadImage("assets/textures/EvilSnake.png");
    if (icon.width == 0 || icon.height == 0) {
        TraceLog(LOG_WARNING, "Failed to load application icon.");
        return;
    }
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void GameUtils::takeScreenshot()
{
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);
    char timeBuffer[32];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d_%H-%M-%S", localTime);
    std::string filename = "Screenshot_" + std::string(timeBuffer) + ".png";
    TakeScreenshot(filename.c_str());
}

std::string GameUtils::getFormattedGameTime(float startTime, float until)
{
    float elapsedTime = until - startTime;
    int minutes = (int) (elapsedTime) / 60;
    int seconds = (int) (elapsedTime) % 60;
    int milliseconds = (int) ((elapsedTime - (int) (elapsedTime)) * 100);
    return std::format("{:02}:{:02}:{:02}", minutes, seconds, milliseconds);
}

std::string GameUtils::getFormattedGameMode(GameMode mode)
{
    switch (mode) {
        case GameMode::NORMAL:
            return "Normal";
        case GameMode::FAST:
            return "Fast";
        case GameMode::WALLS:
            return "Walls";
        default:
            return "";
    }
}

Vector2 GameUtils::getRandomGridPosition()
{
    int x = GetRandomValue(0, Constants::CELL_AMOUNT_X - 1) * Constants::CELL_SIZE;
    int y = GetRandomValue(0, Constants::CELL_AMOUNT_Y - 1) * Constants::CELL_SIZE;
    return {(float) (x), (float) (y)};
}

Vector2 GameUtils::getRandomFoodPosition(
    const std::vector<Vector2> &snakePosition, const std::vector<Vector2> &wallPositions)
{
    Vector2 position;
    bool onSnake, onWall;

    do {
        position = getRandomGridPosition();
        onSnake = isPositionOnSnake(position, snakePosition);
        onWall = std::any_of(wallPositions.begin(), wallPositions.end(),
            [&](const Vector2 &wall) { return position.x == wall.x && position.y == wall.y; });
    } while (onSnake || onWall);

    return position;
}

Vector2 GameUtils::getRandomWallPosition(const std::vector<Vector2> &snakePosition, const Vector2 &foodPosition)
{
    Vector2 position;
    do {
        position = getRandomGridPosition();
    } while (
        isPositionOnSnake(position, snakePosition) || (position.x == foodPosition.x && position.y == foodPosition.y));
    return position;
}

std::string GameUtils::assetPath()
{
    const char *workingDir = GetApplicationDirectory();
    std::string fullPath = std::string(workingDir);

    size_t pos = fullPath.find_last_of("/");
    if (pos != std::string::npos) {
        pos = fullPath.find_last_of("/", pos - 1);
    }

    if (pos != std::string::npos) {
        fullPath = fullPath.substr(0, pos);
    }

#ifdef MACOS_BUILD
    fullPath += "/Resources";
#endif

    fullPath += "/assets/";
    return fullPath;
}
