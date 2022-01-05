#include "window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <string>

// public functions
window::window() {
  win = nullptr;
  renderer = nullptr;
  filepath = nullptr;
  shift_x_pairs['1'] = '!';
  shift_x_pairs['2'] = '@';
  shift_x_pairs['3'] = '#';
  shift_x_pairs['4'] = '$';
  shift_x_pairs['5'] = '%';
  shift_x_pairs['6'] = '^';
  shift_x_pairs['7'] = '&';
  shift_x_pairs['8'] = '*';
  shift_x_pairs['9'] = '(';
  shift_x_pairs['0'] = ')';
  shift_x_pairs[';'] = ':';
  shift_x_pairs[','] = '<';
  shift_x_pairs['.'] = '>';
  shift_x_pairs['/'] = '?';
  shift_x_pairs['['] = '{';
  shift_x_pairs[']'] = '}';
  shift_x_pairs['-'] = '_';
  shift_x_pairs['='] = '+';
}

window::~window() { destroy(); }

void window::destroy() {
  writetofile();
  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(renderer);
  win = nullptr;
  renderer = nullptr;
}

void window::writetofile() {
  std::ofstream file(filepath);
  if (file.is_open()) {
    file << text;
    file.close();
  } else {
    std::cout << "Error writing back to file " << filepath << std::endl;
  }
}

bool window::init() {
  int WIDTH = 640;
  int HEIGHT = 480;
  int X_POS = 0;
  int Y_POS = 0;

  win = SDL_CreateWindow("Text Editor", X_POS, Y_POS, WIDTH, HEIGHT,
                         SDL_WINDOW_RESIZABLE);
  if (!win) {
    std::cout << "Creating window failed with error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  renderer = SDL_CreateRenderer(win, -1, 0);
  if (!renderer) {
    std::cout << "Creating renderer failed with error: " << SDL_GetError()
              << std::endl;
  }
  renderemptyscreen();
  return true;
}

void window::centerwindow(float resize_relocate_ratio) {
  SDL_Rect rect;
  SDL_GetDisplayBounds(0, &rect);
  int NEW_WIDTH = rect.w * resize_relocate_ratio;
  int NEW_HEIGHT = rect.h * resize_relocate_ratio;
  resizewindow(NEW_WIDTH, NEW_HEIGHT);
  movewindow((rect.w - NEW_WIDTH) / 2, (rect.h - NEW_HEIGHT) / 2);
}

void window::run() {
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYUP:
        handlekbup(e);
        break;
      case SDL_KEYDOWN:
        handlekbdown(e);
        break;
      }
    }
  }
}

void window::handlekbup(SDL_Event e) {
  switch (e.key.keysym.sym) {
  case SDLK_LSHIFT:
  case SDLK_RSHIFT:
    shiftdown = false;
    break;
  case SDLK_COLON:
    std::cout << "Colon key lifted" << std::endl;
    break;
  }
}

void window::handlekbdown(SDL_Event e) {
  char c;
  switch (e.key.keysym.sym) {
  case SDLK_RSHIFT:
  case SDLK_LSHIFT:
    shiftdown = true;
    return;
  case SDLK_CAPSLOCK:
    capslock = !capslock;
    return;
  case SDLK_SPACE:
    c = ' ';
    break;
  case SDLK_KP_ENTER:
    c = '\n';
    break;
  case SDLK_BACKSPACE:
    if (text.size() > 0)
      text.pop_back();
    rendertext();
    return;
  default:
    c = *SDL_GetKeyName(e.key.keysym.sym);
  }
  text += cleanchar(c);
  rendertext();
}

char window::cleanchar(char c) {
  if (c == '\n')
    return c;
  if (c >= 'A' && c <= 'Z') {
    if (capslock | shiftdown)
      return toupper(c);
    return tolower(c);
  }
  if (c == ' ' || !shiftdown) {
    return c;
  }
  return shift_x_pairs[c];
}

void window::rendersurfacetowindow(SDL_Surface *surface, SDL_Rect *src,
                                   SDL_Rect *dest) {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 19, 19, 19, 255); // red
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_RenderCopy(renderer, texture, src, dest);
  SDL_RenderPresent(renderer);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void window::loadimage(const char *filepath) {
  SDL_Surface *image = loadimagesurface(filepath);
  rendersurfacetowindow(image, NULL, NULL);
}

void window::loadfile(const char *filepath) {
  this->filepath = filepath;
  if (!readfromfile(filepath)) {
    return;
  }
  rendertext();
}

bool window::readfromfile(const char *filepath) {
  std::ifstream file(filepath);
  std::string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      text += line + '\n';
    }
    text.pop_back();
    file.close();
    return true;
  }
  std::cout << "Error opening file: " << filepath << std::endl;
  return false;
}

void window::renderemptyscreen() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 19, 19, 19, 255); // red
  SDL_RenderPresent(renderer);
}

void window::rendertext() {
  if (!text.size()) {
    renderemptyscreen();
    return;
  }
  TTF_Font *font = TTF_OpenFont("Open_Sans/sans.ttf", 25); // sans
  const char *cleanedtext = stringtochar(text);
  // SDL_Surface *textsurface =
  // TTF_RenderText_Solid(font, cleanedtext, white); // create text surface
  SDL_Rect rect;
  SDL_GetDisplayBounds(0, &rect);
  SDL_Color white = {255, 255, 255, 255};

  SDL_Surface *textsurface =
      TTF_RenderText_Blended_Wrapped(font, cleanedtext, white, rect.w);
  if (!textsurface) {
    std::cout << "Error loading text surface: " << SDL_GetError() << std::endl;
    return;
  }
  SDL_Rect dest;
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  dest.x = 0;
  dest.y = 0;
  // dest.w = w * ();
  dest.w = text.size() * 5; // 5px per char
  dest.h = h / fontsize;
  rendersurfacetowindow(textsurface, NULL, &dest);
  delete[] cleanedtext;
}

// private functions
std::string window::chartostring(const char *cstr) {
  std::string str(cstr);
  return str;
}

const char *window::stringtochar(std::string str) {
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  return cstr;
}

SDL_Surface *window::loadimagesurface(const char *filepath) {
  return IMG_Load(filepath);
}

SDL_Surface *window::getwindowsurface() { return SDL_GetWindowSurface(win); }

void window::blitsurface(SDL_Surface *src, SDL_Surface *dest) {
  SDL_BlitSurface(src, NULL, dest, NULL);
}

void window::updatewindow() { SDL_UpdateWindowSurface(win); }

void window::resizewindow(int width, int height) {
  SDL_SetWindowSize(win, width, height);
}

void window::movewindow(int x, int y) { SDL_SetWindowPosition(win, x, y); }
