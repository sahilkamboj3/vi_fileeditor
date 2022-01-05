#pragma once
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
  void loadimage(const char *filepath);
  void loadfile(const char *filepath);
  void run();

private:
  // variables
  SDL_Window *win;
  SDL_Renderer *renderer;
  const char *filepath;
  std::string text;
  bool capslock = false;
  bool shiftdown = false;
  std::unordered_map<char, char> shift_x_pairs;

  // render functions
  void rendersurfacetowindow(SDL_Surface *surface, SDL_Rect *src,
                             SDL_Rect *dest);
  void rendertext();
  void renderemptyscreen();

  // helper functions
  SDL_Surface *getwindowsurface();
  SDL_Surface *loadimagesurface(const char *filepath);
  bool readfromfile(const char *filepath);
  void writetofile();
  void handlekbdown(SDL_Event e);
  void handlekbup(SDL_Event e);
  void handletextinput(SDL_Event e);
  void blitsurface(SDL_Surface *src, SDL_Surface *dest);
  void updatewindow();
  void resizewindow(int width, int height);
  void movewindow(int x, int y);
  std::string chartostring(const char *str);
  const char *stringtochar(std::string str);
  char cleanchar(char c);
  void destroy();
};
