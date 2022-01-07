#pragma once
#include "line.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class window {
public:
  // window.cpp
  window();
  ~window();
  bool init();
  void loadfile(std::string filepath);
  void run();

private:
  // variables
  SDL_Window *win;
  SDL_Renderer *renderer;
  int tabtospace = 4;
  enum modetype { VISUAL, INSERT };
  modetype mode = VISUAL;
  std::vector<line> lines;
  void destroy();

  // window_file.cpp
  std::string filepath;
  bool readfromfile(std::string filepath);
  void writetofile();

  // window_kb.cpp
  bool capslock = false;
  bool shiftdown = false;
  std::unordered_map<char, char> shift_x_pairs;
  void handlekbdown(SDL_Event e);
  void handlekbdownvisualmode(SDL_Event e);
  void handlekbdowninsertmode(SDL_Event e);
  void handlekbup(SDL_Event e);
  void handletextinput(SDL_Event e);
  void incrementlinefocus();
  void decrementlinefocus();
  std::string chartostring(const char *str);
  const char *stringtochar(std::string str);
  char cleanchar(char c);

  // window_render.cpp
  int linerenderstartidx = 0;
  int linesrendering = 0;
  const char *myfont = stringtochar("Courier_Prime/CourierPrime-Bold.ttf");
  int fontsize = 20;
  const int lineheight = 25;
  int focuslineidx = 0;
  void setlinerenderendidx();
  void rendervimmode();
  void renderclear();
  void renderpresent();
  void renderlines();
  void renderemptyscreen();
  void copysurfacetorenderer(SDL_Surface *surface, SDL_Rect *src,
                             SDL_Rect *dest);
  void blitsurface(SDL_Surface *src, SDL_Surface *dest);

  // window_window.cpp
  int windowheight = 0;
  int windowwidth = 0;
  int vimbackgroundheight = 0;
  void setvimbackgroundheight();
  void setwindowheightwidth();
  void centerwindow(float resize_relocate_ratio);
  SDL_Surface *getwindowsurface();
  void updatewindow();
  void resizewindow(int width, int height);
  void movewindow(int x, int y);
  void setlinesrendering();
};
