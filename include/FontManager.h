#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <unordered_map>

#include "raylib.h"

class FontManager
{
   public:
    static FontManager &getInstance();

    void initFonts();
    Font getFont(int fontId) const;

    static const int FONT_MAIN;
    static const int FONT_TITLE;

   private:
    FontManager();
    ~FontManager();

    FontManager(const FontManager &) = delete;
    FontManager &operator=(const FontManager &) = delete;

    std::unordered_map<int, Font> fonts;
};

#endif
