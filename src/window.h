#pragma once
#include "line.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
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
  bool loadfile(std::string filepath);
  void run();

private:
  typedef enum mode { VISUAL, INSERT } MODE;

  // new variables setup
  SDL_Color WHITE = {255, 255, 255, 255};
  SDL_Color DARKGREY = {38, 38, 38, 255};
  SDL_Color RED = {255, 0, 0, 255};

  std::string FONTNAME = "SpaceMono.ttf";
  int WINDOW_WIDTH = 750;
  int WINDOW_HEIGHT = 500;
  const char *FONT = stringtochar(FONTNAME);
  const int FONTSIZE = 15;
  const int TABTOSPACE = 4;
  const int GOLDFPS = 60;
  const int FRAMERATE = 1000 / GOLDFPS;

  bool capslock, shiftdown = false;
  SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;
  int numlinedigits, numlinesonwindow;
  int charsperline;
  std::vector<line> lines;
  MODE mode;
  int lineheight, letterwidth;

  int focuslineidx = 0, cursorindex = 0, startingletterrenderidx = 0,
      startinglinerenderidx = 0;
  std::string filepath;
  std::unordered_map<char, char> shift_x_pairs;
  std::string userinputs;
  line cpline;

  void destroy();

  // window_kb.cpp
  void setcapslock();
  void handlekbup(SDL_Event e);
  // void handlekbdown(SDL_Event e);
  // void handlekbdownvisualmode(SDL_Event e);
  // void handlekbdowninsertmode(SDL_Event e);
  void handletextinput(const char *c);
  void handletextinputinsertmode(const char *c);
  void handletextinputvisualmode(const char *c);

  char cleanchar(char c);
  void incrementfocusline();
  void decrementfocusline();
  bool handleshiftplusxkeys(char c);
  void handleuserinput(char c,
                       bool insert); // for handling multiple char vim commands

  // window_window.cpp
  void centerwindow(float resize_relocate_ratio);
  void resizewindow(int width, int height);
  void movewindow(int x, int y);
  void setwindowwidthheight();
  void setlineheightandletterwidth();
  void setnumlinesonwindow();
  void setcharsperline();
  int getdisplaywidth();
  int getdisplayheight();

  // window_render.cpp
  void renderscreen();
  void renderemptyscreen();
  void renderclear();
  void renderpresent();
  void renderbackground();
  void rendercursor();
  void rendervimmode();
  void renderlineletterslot();
  void renderlines();
  void copysurfacetorenderer(SDL_Surface *surface, SDL_Rect *src,
                             SDL_Rect *dest);

  // window_file.cpp
  bool readfromfile(std::string filepath);
  void writetofile();

  // window_util.cpp
  const char *stringtochar(std::string &str);
  const char *inttochar(int num);
  std::string chartostring(const char *cstr);
  std::string inttostring(int num);
  std::string getfilenamefromfilepath(std::string filepath);
  int getnumdigits(int num);
};
