#include "window/window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

int main(int argc, char *argv[]) {
  window w;
  SDL_Window *window;

  if (!w.init() || !(window = w.createwindow())) {
    return EXIT_FAILURE;
  }
  // resizing window because rect dimensions not retrievable in createwindow()
  w.centerwindow(window, 0.75);
  // w.addimage("ball.png");
  // w.addimage("ball2.png");

  w.run(window);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
