#include "window.h"
#include "../../include/SDL2/SDL_image.h"
#include <SDL2/SDL.h>
#include <iostream>

void window::run() {
  if (!_init()) {
    return;
  }
  if (!_loadimage("ball.jpg")) {
    return;
  }
  _blitsurface(_image, _wsurface);
  _updatewindowsurface();
  _delay(3000);

  /*
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        quit = true;
        break;
      }
    }
  }
  */

  _destroy();
}

bool window::_init() {
  bool status = true;
  int WIDTH = 750;
  int HEIGHT = 750;
  int X_POS = 100;
  int Y_POS = 125;

  _win = SDL_CreateWindow("Text Editor", X_POS, Y_POS, WIDTH, HEIGHT,
                          SDL_WINDOW_RESIZABLE);
  if (!_win) {
    SDL_Log("Error creating editor: %s", SDL_GetError());
    status = false;
  }
  _wsurface = SDL_GetWindowSurface(_win);
  if (!_wsurface) {
    SDL_Log("Error creating _window surface: %s", SDL_GetError());
    status = false;
  }
  return status;
}

bool window::_loadimage(const char *filepath) {
  bool status = true;
  _image = IMG_Load(filepath);
  // _image = SDL_LoadBMP(filepath);
  if (!_image) {
    SDL_Log("Error creating bball image surface: %s", SDL_GetError());
    status = false;
  }
  return status;
}

void window::_blitsurface(SDL_Surface *src, SDL_Surface *dest) {
  SDL_BlitSurface(src, NULL, dest, NULL);
}

void window::_updatewindowsurface() { SDL_UpdateWindowSurface(_win); }

void window::_delay(uint32_t delay) { SDL_Delay(delay); }

void window::_destroy() {
  SDL_FreeSurface(_image);
  SDL_DestroyWindow(_win);
  _image = NULL;
  _win = NULL;
  SDL_Quit();
}
