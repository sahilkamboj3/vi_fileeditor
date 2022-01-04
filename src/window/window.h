#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

class window {
public:
  ~window();
  bool init();
  SDL_Window *createwindow();
  // void addimage(const char *filepath);
  // void removeimage(const char *filepath);
  void loadimage(SDL_Window *window, const char *filepath);
  void loadimage(SDL_Window *window, SDL_Surface *filepath);
  void run(SDL_Window *window);
  void centerwindow(SDL_Window *window, float resize_relocate_ratio);

private:
  // std::vector<SDL_Surface *> images;

  void destroy();
  SDL_Surface *loadimagesurface(const char *filepath);
  SDL_Surface *getwindowsurface(SDL_Window *window);
  void blitsurface(SDL_Surface *src, SDL_Surface *dest);
  void updatewindow(SDL_Window *window);
  void resizewindow(SDL_Window *window, int width, int height);
  void movewindow(SDL_Window *window, int x, int y);
};
