#include "sdl.h"
#include "window.h"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
  window w;

  if (!sdl_init() || !w.init()) {
    return EXIT_FAILURE;
  }
  // resizing window because rect dimensions not retrievable in createwindow()
  w.loadfile(argv[argc - 1]);
  w.run();
  sdl_quit();

  return EXIT_SUCCESS;
}
