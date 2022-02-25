/*
#include "sdl.h"
#include "window.h"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
  window w;

  if (!w.loadfile(argv[argc - 1]) || !sdl_init() || !w.init()) {
    return EXIT_FAILURE;
  }

  // resizing window because rect dimensions not retrievable in createwindow()
  w.run();
  sdl_quit();

  return EXIT_SUCCESS;
}
*/

#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *win =
      SDL_CreateWindow("File Editor", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
  SDL_RenderClear(ren);
  SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);

  SDL_RenderPresent(ren);

  bool quit = false;
  std::cout << quit << std::endl;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        quit = true;
        break;
      }
    }
  }
  return 0;
}
