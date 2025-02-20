#include "../include/font_manager.h"

#include <raylib.h>

#include "../include/game_utils.h"

const int FontManager::FONT_MAIN = 1;
const int FontManager::FONT_TITLE = 2;

FontManager::FontManager() {}

FontManager::~FontManager()
{
    for (auto &fontPair : fonts) {
        UnloadFont(fontPair.second);
    }
}

FontManager &FontManager::getInstance()
{
    static FontManager instance;
    return instance;
}

void FontManager::initFonts()
{
    fonts[FONT_MAIN] = LoadFontEx(TextFormat("%sfonts/Thaleah.ttf", GameUtils::getAssetPath().c_str()), 256, 0, 250);
    fonts[FONT_TITLE] = LoadFontEx(TextFormat("%sfonts/Round.ttf", GameUtils::getAssetPath().c_str()), 256, 0, 250);
}

Font FontManager::getFont(int fontId) const
{
    auto fontMap = fonts.find(fontId);
    if (fontMap != fonts.end()) {
        return fontMap->second;
    }
    return Font{};
}
