#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

class window {
public:
  window();
  ~window();
  bool init();
  void loadimage(const char *filepath);
  void loadimage(SDL_Surface *filepath);
  void run();
  void centerwindow(float resize_relocate_ratio);

private:
  SDL_Window *win;

  void destroy();
  SDL_Surface *loadimagesurface(const char *filepath);
  SDL_Surface *getwindowsurface();
  void blitsurface(SDL_Surface *src, SDL_Surface *dest);
  void updatewindow();
  void resizewindow(int width, int height);
  void movewindow(int x, int y);
};
