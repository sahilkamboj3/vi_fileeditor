#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class line {
public:
  line();
  line(std::string text);
  void addchar(char &c);
  void addchar(char &c, size_t idx);
  void addstr(std::string &s);
  void addstr(std::string &s, size_t idx);
  void popchar();
  void popchar(size_t idx);
  void removestr(int idx);
  std::string gettext();
  std::string gettext(int start);
  std::string gettext(int start, int length);

private:
  std::string text;
};
