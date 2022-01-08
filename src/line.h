#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class line {
public:
  line(int linenum);
  line(std::string text, int linenum);
  void addchar(char &c);
  void addstr(std::string &s);
  void popchar();
  std::string gettext();
  std::string gettext(int start, int length);
  int getlinenum();

private:
  std::string text;
  int linenum;
};
