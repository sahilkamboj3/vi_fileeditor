#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class line {
public:
  line(int linenum);
  line(std::string text, int linenum);
  void addchar(char &c);
  void addchar(char &c, size_t idx);
  void addstr(std::string &s);
  void addstr(std::string &s, size_t idx);
  void popchar();
  void popchar(size_t idx);
  std::string gettext();
  std::string gettext(int start, int length);
  int getlinenum();

private:
  std::string text;
  int linenum;
};
