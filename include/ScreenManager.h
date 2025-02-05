#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <string>

class ScreenManager {
public:
  static ScreenManager &getInstance();

  void drawMenuScreen();
  void drawPlayingScreen(int score, std::string gameMode, std::string time);
  void drawPauseScreen(int score, std::string time);
  void drawGameOverScreen(int score, std::string time);
  void drawGameFinishedScreen(int score, std::string time);

private:
  ScreenManager();
  ~ScreenManager();

  ScreenManager(const ScreenManager &) = delete;
  ScreenManager &operator=(const ScreenManager &) = delete;
};

#endif
