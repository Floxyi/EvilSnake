#include "../include/GameUtils.h"

#include <raylib.h>

#include <ctime>
#include <sstream>

#include "../include/Constants.h"
#include "../include/GameMode.h"

namespace
{

bool isPositionOnSnake(Vector2 position, const std::vector<Vector2> &snakePosition)
{
    for (const Vector2 &bodyPart : snakePosition) {
        if (bodyPart.x == position.x && bodyPart.y == position.y) {
            return true;
        }
    }
    return false;
}

}  // namespace

void GameUtils::applyApplicationIcon()
{
    Image icon = LoadImage("assets/textures/EvilSnake.png");
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

    int minutes = static_cast<int>(elapsedTime) / 60;
    int seconds = static_cast<int>(elapsedTime) % 60;
    int milliseconds = static_cast<int>((elapsedTime - static_cast<int>(elapsedTime)) * 100);

    std::ostringstream timeStream;
    timeStream << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << ":"
               << (milliseconds < 10 ? "0" : "") << milliseconds;

    return timeStream.str();
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
    }
    return "";
}

Vector2 GameUtils::getRandomGridPosition()
{
    int x = GetRandomValue(0, Constants::CELL_AMOUNT_X - 1) * Constants::CELL_SIZE;
    int y = GetRandomValue(0, Constants::CELL_AMOUNT_Y - 1) * Constants::CELL_SIZE;
    return {static_cast<float>(x), static_cast<float>(y)};
}

Vector2 GameUtils::getRandomFoodPosition(
    const std::vector<Vector2> &snakePosition, const std::vector<Vector2> &wallPositions)
{
    Vector2 position;
    bool onWall = false;
    bool onSnake = false;

    do {
        position = getRandomGridPosition();
        onWall = std::any_of(wallPositions.begin(), wallPositions.end(),
            [&](const Vector2 &wall) { return position.x == wall.x && position.y == wall.y; });
        onSnake = isPositionOnSnake(position, snakePosition);
    } while (onSnake || onWall);

    return position;
}

Vector2 GameUtils::getRandomWallPosition(const std::vector<Vector2> &snakePosition, const Vector2 &foodPosition)
{
    Vector2 position;
    bool onFood = false;
    bool onSnake = false;

    do {
        position = getRandomGridPosition();
        onFood = (position.x == foodPosition.x && position.y == foodPosition.y);
        onSnake = isPositionOnSnake(position, snakePosition);
    } while (onSnake || onFood);

    return position;
}
