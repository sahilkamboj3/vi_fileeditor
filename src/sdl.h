#include <SDL2/SDL.h>
#include <iostream>

bool sdl_init() {
  if (SDL_Init(SDL_INIT_AUDIO)) {
    std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

void sdl_quit() { SDL_Quit(); }
