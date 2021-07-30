#pragma once

#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace font_size {
enum {
  x36 = 0,
  x16,
  count,
};
}  

class FontManager {
  TTF_Font *fonts_[font_size::count];

  inline void load(const char *path, unsigned int size,
                   const unsigned char font_size) noexcept {
    fonts_[font_size] = TTF_OpenFont(path, size);
    if (!fonts_[font_size]) {
      std::cerr << "error: " << TTF_GetError() << '\n';
      exit(EXIT_FAILURE);
    }
  }

 public:
  FontManager() noexcept {
    if (TTF_Init() == -1) {
      std::cerr << "error: " << TTF_GetError() << '\n';
      exit(EXIT_FAILURE);
    }
    load("./resources/graphics/bold_font.otf", 36, font_size::x36);
    load("./resources/graphics/light_font.otf", 16, font_size::x16);
  }

  inline TTF_Font *get(const unsigned char font_size) const noexcept {
    return fonts_[font_size];
  }

  ~FontManager() noexcept {
    for (const auto &font : fonts_) {
      TTF_CloseFont(font);
    }
    atexit(TTF_Quit);
  }
};
