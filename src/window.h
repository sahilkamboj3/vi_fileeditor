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
  void loadfile(std::string filepath);
  void run();

private:
  /*
  typedef struct color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    color() : r(0), g(0), b(0), a(0) {}

    color(int r, int g, int b, int a) {
      this->r = r;
      this->g = g;
      this->b = b;
      this->a = a;
    }
  } COLOR;
  */

  typedef enum mode { VISUAL, INSERT } MODE;

  // new variables setup
  std::string FONTNAME = "SpaceMono.ttf";
  const char *FONT = stringtochar(FONTNAME);
  const int FONTSIZE = 15;
  const int TABTOSPACE = 4;
  // const COLOR WHITE{255, 255, 255, 255};
  // const COLOR DARKGREY{38, 38, 38, 255};
  // const COLOR RED{255, 0, 0, 255};
  SDL_Color WHITE = {255, 255, 255, 255};
  SDL_Color DARKGREY = {38, 38, 38, 255};
  SDL_Color RED = {255, 0, 0, 255};
  int GOLDFPS = 60;
  bool capslock, shiftdown = false;
  // cursorindex indicates the letter user is on, startingletterrenderidx and
  // startinglinerenderidx indicate index to start rendering the letter and line
  int focuslineidx = 0, cursorindex = 0, startingletterrenderidx = 0,
      startinglinerenderidx = 0;
  int linesizedigits, numlinesonwindow;
  int charsperline;
  SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;
  std::vector<line> lines;
  std::string filepath;
  std::unordered_map<char, char> shift_x_pairs;
  int windowwidth, windowheight;
  int lineheight, letterwidth;
  MODE mode;
  std::string userinputs;
  line cpline;

  void destroy();

  // window_kb.cpp
  void handlekbup(SDL_Event e);
  void handlekbdown(SDL_Event e);
  void handlekbdownvisualmode(SDL_Event e);
  void handlekbdowninsertmode(SDL_Event e);
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

  // window_render.cpp
  void renderclear();
  void renderpresent();
  void renderemptyscreen();
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
  void setcapslock();
};
