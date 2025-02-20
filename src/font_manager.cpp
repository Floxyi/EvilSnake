/**
 * @file font_manager.cpp
 * @brief Implementation of the FontManager singleton class
 *
 * This file implements a font resource manager that handles loading,
 * storing, and providing access to different fonts used in the game.
 * It follows the singleton pattern to ensure a single point of font management.
 */

#include "../include/font_manager.h"

#include <raylib.h>

#include "../include/game_utils.h"

/**
 * @brief Font identifier for the main game font
 * Used for regular text throughout the game
 */
const int FontManager::FONT_MAIN = 1;

/**
 * @brief Font identifier for the title font
 * Used for headings and important UI elements
 */
const int FontManager::FONT_TITLE = 2;

/**
 * @brief Default constructor
 *
 * Private constructor as part of the singleton pattern.
 * Fonts are not loaded here but in initFonts() to allow for proper resource management.
 */
FontManager::FontManager() {}

/**
 * @brief Destructor
 *
 * Properly unloads all fonts from memory when the FontManager is destroyed.
 * This prevents memory leaks and ensures proper cleanup of font resources.
 */
FontManager::~FontManager()
{
    for (auto &fontPair : fonts) {
        UnloadFont(fontPair.second);
    }
}

/**
 * @brief Gets the singleton instance of FontManager
 *
 * @return FontManager& Reference to the singleton instance
 *
 * Implements the singleton pattern using local static initialization,
 * which is thread-safe in C++11 and later.
 */
FontManager &FontManager::getInstance()
{
    static FontManager instance;
    return instance;
}

/**
 * @brief Initializes and loads all game fonts
 *
 * Loads the following fonts from the assets directory:
 * - Thaleah.ttf as the main font (FONT_MAIN)
 * - Round.ttf as the title font (FONT_TITLE)
 *
 * Each font is loaded with the following parameters:
 * - Font size: 256
 * - No specific chars to load (0)
 * - Maximum of 250 characters
 */
void FontManager::initFonts()
{
    fonts[FONT_MAIN] = LoadFontEx(TextFormat("%sfonts/Thaleah.ttf", GameUtils::getAssetPath().c_str()), 256, 0, 250);
    fonts[FONT_TITLE] = LoadFontEx(TextFormat("%sfonts/Round.ttf", GameUtils::getAssetPath().c_str()), 256, 0, 250);
}

/**
 * @brief Retrieves a font by its identifier
 *
 * @param fontId The identifier of the font to retrieve (FONT_MAIN or FONT_TITLE)
 * @return Font The requested font, or an empty Font object if the ID is not found
 *
 * This method provides safe access to loaded fonts. If the requested font ID
 * doesn't exist, it returns an empty Font object rather than throwing an exception.
 */
Font FontManager::getFont(int fontId) const
{
    auto fontMap = fonts.find(fontId);
    if (fontMap != fonts.end()) {
        return fontMap->second;
    }
    return Font{};
}
