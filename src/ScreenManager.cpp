#include "../include/ScreenManager.h"
#include "../include/FontManager.h"
#include "../include/TextUtils.h"

ScreenManager::ScreenManager() {}

ScreenManager::~ScreenManager() {}

ScreenManager &ScreenManager::getInstance() {
  static ScreenManager
      instance; // This creates a static instance, initialized once.
  return instance;
}

void ScreenManager::drawMenuScreen() {
  TextUtils::drawAlignedText("EvilSnake", FontManager::FONT_TITLE, 80, DARKGRAY,
                             VerticalAlignment::TOP,
                             HorizontalAlignment::CENTER, 60);
  TextUtils::drawAlignedText(
      "Press the [ARROW KEYS / WASD] key to start and play the game",
      FontManager::FONT_MAIN, 25, DARKGRAY, VerticalAlignment::TOP,
      HorizontalAlignment::CENTER, 180);
  TextUtils::drawAlignedText("Made by Florian", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::LEFT, 10);
  TextUtils::drawAlignedText("[ESC] - Quit", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 10);
  TextUtils::drawAlignedText("[J/K] - Pause/Continue", FontManager::FONT_MAIN,
                             20, DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 30);
  TextUtils::drawAlignedText(
      "[Space] - Quit to main menu", FontManager::FONT_MAIN, 20, DARKGRAY,
      VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER, 50);
  TextUtils::drawAlignedText("[L] - Screenshot", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 70);
  TextUtils::drawAlignedText("v1.0", FontManager::FONT_MAIN, 20, DARKGRAY,
                             VerticalAlignment::BOTTOM,
                             HorizontalAlignment::RIGHT, 10);
}

void ScreenManager::drawPlayingScreen(int score, std::string gameMode,
                                      std::string time) {
  TextUtils::drawAlignedText(
      ("Score: " + std::to_string(score)).c_str(), FontManager::FONT_MAIN, 30,
      DARKGRAY, VerticalAlignment::TOP, HorizontalAlignment::RIGHT, 10);
  TextUtils::drawAlignedText(
      ("Mode: " + gameMode).c_str(), FontManager::FONT_MAIN, 30, DARKGRAY,
      VerticalAlignment::TOP, HorizontalAlignment::CENTER, 10);
  TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN,
                             30, DARKGRAY, VerticalAlignment::TOP,
                             HorizontalAlignment::LEFT, 10);
  TextUtils::drawAlignedText(
      "[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 20, DARKGRAY,
      VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER, 10);
  TextUtils::drawAlignedText("[J] - Pause", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 30);
}

void ScreenManager::drawPauseScreen(int score, std::string time) {
  TextUtils::drawAlignedText("Pause", FontManager::FONT_MAIN, 60, DARKGRAY,
                             VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -120);
  TextUtils::drawAlignedText(
      ("Score: " + std::to_string(score)).c_str(), FontManager::FONT_MAIN, 30,
      DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50);
  TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN,
                             30, DARKGRAY, VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -70);
  TextUtils::drawAlignedText(
      "[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 20, DARKGRAY,
      VerticalAlignment::BOTTOM, HorizontalAlignment::CENTER, 10);
  TextUtils::drawAlignedText("[K] - Continue", FontManager::FONT_MAIN, 20,
                             DARKGRAY, VerticalAlignment::BOTTOM,
                             HorizontalAlignment::CENTER, 30);
}

void ScreenManager::drawGameOverScreen(int score, std::string time) {
  TextUtils::drawAlignedText("GAME OVER", FontManager::FONT_MAIN, 60, DARKGRAY,
                             VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -120);
  TextUtils::drawAlignedText(
      ("Score: " + std::to_string(score)).c_str(), FontManager::FONT_MAIN, 30,
      DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50);
  TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN,
                             30, DARKGRAY, VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -70);
  TextUtils::drawAlignedText(
      "[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 30, DARKGRAY,
      VerticalAlignment::CENTER, HorizontalAlignment::CENTER, 50);
}

void ScreenManager::drawGameFinishedScreen(int score, std::string time) {
  TextUtils::drawAlignedText(
      "YOU WON, CONGRATULATIONS!", FontManager::FONT_MAIN, 60, DARKGRAY,
      VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -120);
  TextUtils::drawAlignedText(
      ("Score: " + std::to_string(score)).c_str(), FontManager::FONT_MAIN, 30,
      DARKGRAY, VerticalAlignment::CENTER, HorizontalAlignment::CENTER, -50);
  TextUtils::drawAlignedText(("Time: " + time).c_str(), FontManager::FONT_MAIN,
                             30, DARKGRAY, VerticalAlignment::CENTER,
                             HorizontalAlignment::CENTER, -70);
  TextUtils::drawAlignedText(
      "[SPACE] - Quit to main menu", FontManager::FONT_MAIN, 30, DARKGRAY,
      VerticalAlignment::CENTER, HorizontalAlignment::CENTER, 50);
}
