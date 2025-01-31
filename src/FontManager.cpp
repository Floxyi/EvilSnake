#include "../include/FontManager.h"

const int FontManager::FONT_MAIN = 1;
const int FontManager::FONT_TITLE = 2;

FontManager::FontManager() {}

FontManager::~FontManager() {
  for (auto &fontPair : fonts) {
    UnloadFont(fontPair.second);
  }
}

FontManager &FontManager::getInstance() {
  static FontManager instance;
  return instance;
}

void FontManager::initFonts() {
  fonts[FONT_MAIN] = LoadFontEx("assets/fonts/Thaleah.ttf", 256, 0, 250);
  fonts[FONT_TITLE] = LoadFontEx("assets/fonts/Round.ttf", 256, 0, 250);
}

Font FontManager::getFont(int fontId) const {
  auto it = fonts.find(fontId);
  if (it != fonts.end()) {
    return it->second;
  }
  return Font{};
}
