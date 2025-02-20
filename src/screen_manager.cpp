/**
 * @file screen_manager.cpp
 * @brief Implementation of the ScreenManager singleton class
 *
 * This file implements a screen manager that handles the rendering of different
 * game screens (menu, playing, pause, game over, and finished states). It manages
 * the layout and positioning of UI elements using aligned text rendering.
 */

#include "../include/screen_manager.h"

#include "../include/font_manager.h"
#include "../include/text_utils.h"

/**
 * @brief Default constructor
 *
 * Private constructor as part of the singleton pattern.
 */
ScreenManager::ScreenManager() {}

/**
 * @brief Destructor
 */
ScreenManager::~ScreenManager() {}

/**
 * @brief Gets the singleton instance of ScreenManager
 *
 * @return ScreenManager& Reference to the singleton instance
 *
 * Implements the singleton pattern using local static initialization,
 * which is thread-safe in C++11 and later.
 */
ScreenManager &ScreenManager::getInstance()
{
    static ScreenManager instance;
    return instance;
}

/**
 * @brief Renders the main menu screen
 *
 * Displays:
 * - Game title
 * - Control instructions
 * - Game objective
 * - Credits
 * - Version information
 * - Available commands (screenshots, quit)
 *
 * All text elements are positioned using alignment-based positioning
 * for consistent layout across different screen sizes.
 */
void ScreenManager::drawMenuScreen()
{
    TextUtils::drawAlignedText(
        "EVILSNAKE", FontManager::FONT_TITLE, 80, DARKGRAY, VerticalAlignment::TOP, HorizontalAlignment::CENTER, 60);
    TextUtils::drawAlignedText("Press the [ARROW KEYS / WASD] to start and play the game", FontManager::FONT_MAIN, 25,
        DARKGRAY, VerticalAlignment::TOP, HorizontalAlignment::CENTER, 180);
    TextUtils::drawAlignedText("You have to reach a score of 100", FontManager::FONT_MAIN, 20, DARKGRAY,
        VerticalAlignment::TOP, HorizontalAlignment::CENTER, 220);
    TextUtils::drawAlignedText("Made by Florian", FontManager::FONT_MAIN, 20, DARKGRAY, VerticalAlignment::BOTTOM,
        HorizontalAlignment::LEFT, 10);
    TextUtils::drawAlignedText("[ESC] - Quit", FontManager::FONT_MAIN, 20, DARKGRAY, VerticalAlignment::BOTTOM,
        HorizontalAlignment::CENTER, 10);
    TextUtils::drawAlignedText("[L] - Screenshot / [O] Open Screenshots", FontManager::FONT_MAIN, 20, DARKGRAY,
        VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER, 30);
    TextUtils::drawAlignedText(
        "v1.0.0", FontManager::FONT_MAIN, 20, DARKGRAY, VerticalAlignment::BOTTOM, HorizontalAlignment::RIGHT, 10);
}

/**
 * @brief Renders the playing screen with game information
 *
 * @param score Current game score
 * @param gameMode Current game mode string
 * @param time Formatted game time string
 *
 * Displays:
 * - Current score
 * - Game mode
 * - Elapsed time
 * - Available commands (quit, pause)
 */
void ScreenManager::drawPlayingScreen(int score, std::string gameMode, std::string time)
{
    TextUtils::drawAlignedText(("Score: " + std::to_string(score) + "/100").c_str(), FontManager::FONT_MAIN, 30,
        DARKGRAY, VerticalAlignment::TOP, HorizontalAlignment::RIGHT, 10);
    TextUtils::drawAlignedText(("Mode: " + gameMode).c_str(), FontManager::FONT_MAIN, 30, DARKGRAY,
        VerticalAlignment::TOP, HorizontalAlignment::CENTER, 10);
    TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN, 30, DARKGRAY, VerticalAlignment::TOP,
        HorizontalAlignment::LEFT, 10);
    TextUtils::drawAlignedText("[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 20, DARKGRAY,
        VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER, 10);
    TextUtils::drawAlignedText("[J] - Pause", FontManager::FONT_MAIN, 20, DARKGRAY, VerticalAlignment::BOTTOM,
        HorizontalAlignment::CENTER, 30);
}

/**
 * @brief Renders the pause screen
 *
 * @param score Current game score
 * @param time Formatted game time string
 *
 * Displays:
 * - Pause indicator
 * - Current score
 * - Elapsed time
 * - Available commands (quit, continue)
 */
void ScreenManager::drawPauseScreen(int score, std::string time)
{
    TextUtils::drawAlignedText(
        "Pause", FontManager::FONT_MAIN, 60, DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -120);
    TextUtils::drawAlignedText(("Score: " + std::to_string(score) + "/100").c_str(), FontManager::FONT_MAIN, 30,
        DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50);
    TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN, 30, DARKGRAY,
        VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -70);
    TextUtils::drawAlignedText("[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 20, DARKGRAY,
        VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER, 10);
    TextUtils::drawAlignedText("[J] - Continue", FontManager::FONT_MAIN, 20, DARKGRAY, VerticalAlignment::BOTTOM,
        HorizontalAlignment::CENTER, 30);
}

/**
 * @brief Renders the game over screen
 *
 * @param score Final game score
 * @param time Total game time string
 *
 * Displays:
 * - Game over message
 * - Final score
 * - Total time played
 * - Option to return to menu
 */
void ScreenManager::drawGameOverScreen(int score, std::string time)
{
    TextUtils::drawAlignedText("GAME OVER", FontManager::FONT_MAIN, 60, DARKGRAY, VerticalAlignment::CENTER,
        HorizontalAlignment::CENTER, -120);
    TextUtils::drawAlignedText(("Score: " + std::to_string(score) + "/100").c_str(), FontManager::FONT_MAIN, 30,
        DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50);
    TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN, 30, DARKGRAY,
        VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -70);
    TextUtils::drawAlignedText("[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 30, DARKGRAY,
        VerticalAlignment::CENTER, HorizontalAlignment::CENTER, 50);
}

/**
 * @brief Renders the victory screen
 *
 * @param score Final game score
 * @param time Total game time string
 *
 * Displays:
 * - Victory message
 * - Final score
 * - Total time played
 * - Option to return to menu
 */
void ScreenManager::drawFinishedScreen(int score, std::string time)
{
    TextUtils::drawAlignedText("YOU WON, CONGRATULATIONS!", FontManager::FONT_MAIN, 60, DARKGRAY,
        VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -120);
    TextUtils::drawAlignedText(("Score: " + std::to_string(score) + "/100").c_str(), FontManager::FONT_MAIN, 30,
        DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50);
    TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN, 30, DARKGRAY,
        VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -70);
    TextUtils::drawAlignedText("[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 30, DARKGRAY,
        VerticalAlignment::CENTER, HorizontalAlignment::CENTER, 50);
}
