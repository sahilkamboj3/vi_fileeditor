#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class line {
public:
  line(std::string text);
  void addchar(char &c);
  void popchar();
  std::string gettext();

private:
  std::string text;
};
