#pragma once
#include "line.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class window {
public:
  window();
  ~window();
  bool init();
  void centerwindow(float resize_relocate_ratio);
  void loadfile(const char *filepath);
  void run();

private:
  // variables
  enum modetype { VISUAL, INSERT };
  modetype mode = VISUAL;
  bool capslock = false;
  bool shiftdown = false;
  int focuslineidx = 0;
  const int lineheight = 25;
  SDL_Window *win;
  SDL_Renderer *renderer;
  const char *filepath;
  std::unordered_map<char, char> shift_x_pairs;
  std::vector<line> lines;

  // render functions
  void copysurfacetorenderer(SDL_Surface *surface, SDL_Rect *src,
                             SDL_Rect *dest);
  void renderclear();
  void renderpresent();
  void renderlines();
  void renderemptyscreen();

  // helper functions
  SDL_Surface *getwindowsurface();
  bool readfromfile(const char *filepath);
  void writetofile();
  void handlekbdown(SDL_Event e);
  void handlekbdownvisualmode(SDL_Event e);
  void handlekbdowninsertmode(SDL_Event e);
  void handlekbup(SDL_Event e);
  void handletextinput(SDL_Event e);
  void blitsurface(SDL_Surface *src, SDL_Surface *dest);
  void updatewindow();
  void resizewindow(int width, int height);
  void movewindow(int x, int y);
  void incrementlinefocus();
  void decrementlinefocus();
  std::string chartostring(const char *str);
  const char *stringtochar(std::string str);
  char cleanchar(char c);
  void destroy();
};
