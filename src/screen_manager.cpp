#include "../include/screen_manager.h"

#include "../include/font_manager.h"
#include "../include/text_utils.h"

ScreenManager::ScreenManager() {}

ScreenManager::~ScreenManager() {}

ScreenManager &ScreenManager::getInstance()
{
    static ScreenManager instance;
    return instance;
}

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
