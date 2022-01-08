#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

bool sdl_init() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
    return false;
  }
  if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
    std::cout << "IMG_Init failed with error: " << IMG_GetError() << std::endl;
    return false;
  }
  if (TTF_Init() == -1) {
    std::cout << "TTF_Init failed with error: " << TTF_GetError() << std::endl;
    return false;
  }
  return true;
}

void sdl_quit() {
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
