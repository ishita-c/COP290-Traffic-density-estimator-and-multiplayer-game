#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

namespace image {

enum {
  p1 = 0,
  p2,
  bg,
  bg_red,
  bg_green,
  bg_blue,
  food,
  food_counter,
  akabei,
  pinky,
  aosuke,
  guzuta,
  mon_run,
  plate,
  count,
};

} 

class ImageManager {
  std::vector<SDL_Surface *> images_;
  SDL_Renderer *renderer_;
  inline void load(const char *path, const unsigned char image_type) noexcept {
    SDL_Surface *image = IMG_Load(path);
    if (!image) {
      std::cerr << "error: " << IMG_GetError() << '\n';
      exit(EXIT_FAILURE);
    }
    images_[image_type] = image;
  }

 public:
  ImageManager(SDL_Renderer *renderer) noexcept : renderer_(renderer) {
    images_.reserve(image::count);

    const int flag = IMG_INIT_PNG;
    if ((IMG_Init(flag) & flag) != flag) {
      std::cerr << "error: " << IMG_GetError() << '\n';
      exit(EXIT_FAILURE);
    }

    load("./resources/graphics/mario.png", image::p1);
    load("./resources/graphics/luigi.png", image::p2);
    load("./resources/graphics/bg.png", image::bg);
    load("./resources/graphics/bg2.png", image::bg_red);
    load("./resources/graphics/bg3.png", image::bg_green);
    load("./resources/graphics/bg4.png", image::bg_blue);
    load("./resources/graphics/coin.png", image::food);
    load("./resources/graphics/mushroom.png", image::food_counter);
    load("./resources/graphics/rgoomba.png", image::akabei);
    load("./resources/graphics/pgoomba.png", image::pinky);
    load("./resources/graphics/ggoomba.png", image::aosuke);
    load("./resources/graphics/bgoomba.png", image::guzuta);
    load("./resources/graphics/dead_enemy.png", image::mon_run);
    load("./resources/graphics/plate.png", image::plate);
  }

  inline SDL_Texture *get(const unsigned char image_type) const noexcept {
    return SDL_CreateTextureFromSurface(renderer_, images_[image_type]);
  }

  inline void render_copy(SDL_Texture &texture, const SDL_Rect &src,
                          const SDL_Rect &dst) const noexcept {
    SDL_RenderCopy(renderer_, &texture, &src, &dst);
  }

  ~ImageManager() noexcept { atexit(IMG_Quit); }
};
