/**
 * @file game_utils.cpp
 * @brief Implementation of utility functions for the Evil Snake game
 *
 * This file provides various utility functions for game operations including:
 * - Random position generation
 * - Screenshot management
 * - Time formatting
 * - Asset path handling
 * - Game mode string formatting
 */

#include "../include/game_utils.h"

#include <raylib.h>

#include <ctime>
#include <filesystem>
#include <format>
#include <iostream>

#include "../include/constants.h"
#include "../include/game_mode.h"

namespace
{
/**
 * @brief Checks if a position overlaps with any part of the snake
 *
 * @param position Position to check
 * @param snakePosition Vector of snake body positions
 * @return true if position overlaps with snake, false otherwise
 */
bool isPositionOnSnake(Vector2 position, const std::vector<Vector2> &snakePosition)
{
    return std::find_if(snakePosition.begin(), snakePosition.end(), [&](const Vector2 &bodyPart) {
        return bodyPart.x == position.x && bodyPart.y == position.y;
    }) != snakePosition.end();
}

/**
 * @brief Gets the path to the game's resources directory
 *
 * @return std::string Path to resources directory
 *
 * Determines the correct resource path based on the application directory.
 * Handles special case for macOS builds where resources are in a separate bundle.
 */
std::string getResourcesPath()
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

    return fullPath;
}
}  // namespace

/**
 * @brief Sets the application window icon
 *
 * Loads and sets the window icon from the assets directory.
 * Logs a warning if the icon fails to load.
 */
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

/**
 * @brief Takes a screenshot and saves it to the user's Pictures directory
 *
 * Creates a timestamped screenshot file and moves it to a dedicated
 * EvilSnake folder in the user's Pictures directory. Creates the
 * directory if it doesn't exist.
 */
void GameUtils::takeScreenshot()
{
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);
    char timeBuffer[32];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d_%H-%M-%S", localTime);
    std::string filename = "Screenshot_" + std::string(timeBuffer) + ".png";

    TakeScreenshot(filename.c_str());

    std::string picturesDir = "/Users/" + std::string(getenv("USER")) + "/Pictures/EvilSnake/";

    try {
        if (!std::filesystem::exists(picturesDir)) {
            std::filesystem::create_directories(picturesDir);
        }
        std::string finalPath = picturesDir + filename;
        std::filesystem::rename(filename, finalPath);
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        std::cerr << "Error code: " << e.code() << std::endl;
    }
}

/**
 * @brief Opens the screenshots folder in the system's file explorer
 *
 * Creates the screenshots directory if it doesn't exist and
 * opens it using the system's default file explorer.
 */
void GameUtils::openScreenshotsFolder()
{
    std::string screenshotsPath = "/Users/" + std::string(getenv("USER")) + "/Pictures/EvilSnake/";

    if (!std::filesystem::exists(screenshotsPath)) {
        std::filesystem::create_directory(screenshotsPath);
    }

    OpenURL(screenshotsPath.c_str());
}

/**
 * @brief Formats the game time into a string
 *
 * @param startTime The game start time in seconds
 * @param until The end time in seconds
 * @return std::string Formatted time string in "MM:SS:MS" format
 */
std::string GameUtils::getFormattedGameTime(float startTime, float until)
{
    float elapsedTime = until - startTime;
    int minutes = (int) (elapsedTime) / 60;
    int seconds = (int) (elapsedTime) % 60;
    int milliseconds = (int) ((elapsedTime - (int) (elapsedTime)) * 100);
    return std::format("{:02}:{:02}:{:02}", minutes, seconds, milliseconds);
}

/**
 * @brief Converts a GameMode enum to its string representation
 *
 * @param mode The GameMode to convert
 * @return std::string String representation of the game mode
 */
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

/**
 * @brief Generates a random position on the game grid
 *
 * @return Vector2 Random position aligned to the game grid
 */
Vector2 GameUtils::getRandomGridPosition()
{
    int x = GetRandomValue(0, Constants::CELL_AMOUNT_X - 1) * Constants::CELL_SIZE;
    int y = GetRandomValue(0, Constants::CELL_AMOUNT_Y - 1) * Constants::CELL_SIZE;
    return {(float) (x), (float) (y)};
}

/**
 * @brief Generates a random position for food that doesn't overlap with snake or walls
 *
 * @param snakePosition Vector of current snake body positions
 * @param wallPositions Vector of current wall positions
 * @return Vector2 Valid random position for food
 */
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

/**
 * @brief Generates a random position for a wall that doesn't overlap with snake or food
 *
 * @param snakePosition Vector of current snake body positions
 * @param foodPosition Current food position
 * @return Vector2 Valid random position for a wall
 */
Vector2 GameUtils::getRandomWallPosition(const std::vector<Vector2> &snakePosition, const Vector2 &foodPosition)
{
    Vector2 position;
    do {
        position = getRandomGridPosition();
    } while (
        isPositionOnSnake(position, snakePosition) || (position.x == foodPosition.x && position.y == foodPosition.y));
    return position;
}

/**
 * @brief Gets the path to the game's asset directory
 *
 * @return std::string Path to the assets directory
 */
std::string GameUtils::getAssetPath()
{
    std::string resourcePath = getResourcesPath() + "/assets/";
    return resourcePath;
}
