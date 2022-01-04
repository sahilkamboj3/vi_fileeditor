#include "window/window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

bool sdl_init() {
  if (SDL_Init(SDL_INIT_AUDIO)) {
    std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

void sdl_quit() { SDL_Quit(); }

int main(int argc, char *argv[]) {
  window w;

  if (!sdl_init() || !w.init()) {
    return EXIT_FAILURE;
  }
  // resizing window because rect dimensions not retrievable in createwindow()
  w.centerwindow(0.75);
  w.run();
  sdl_quit();

  return 0;
}
