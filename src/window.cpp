#include "window.h"
#include "line.h"
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
    for (line l : lines) {
      std::string text = l.gettext();
      file << text + '\n';
    }
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

void window::loadfile(const char *filepath) {
  if (!readfromfile(filepath)) {
    return;
  }
  renderclear();
  renderlines();
  renderpresent();
}

bool window::readfromfile(const char *filepath) {
  this->filepath = filepath;
  std::ifstream file(filepath);
  std::string fline;
  if (file.is_open()) {
    while (getline(file, fline)) {
      std::cout << "line: " << fline << std::endl;
      line l(fline);
      lines.push_back(l);
    }
    file.close();
    return true;
  }
  std::cout << "Error opening file: " << filepath << std::endl;
  return false;
}

void window::renderlines() {
  if (!lines.size()) {
    renderemptyscreen();
    return;
  }
  // TTF_Font *font = TTF_OpenFont("Open_Sans/sans.ttf", 20); // sans
  TTF_Font *font =
      TTF_OpenFont("Courier_Prime/CourierPrime-Bold.ttf", 20); // sans
  SDL_Color white = {255, 255, 255, 255};
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  SDL_Rect linerect;
  linerect.x = 0;
  linerect.y = 0;
  int linenum = 0;
  for (line l : lines) {
    std::string text = l.gettext();
    if (text.size() > 0) {
      const char *cleanedtext = stringtochar(text);
      SDL_Surface *textsurface =
          TTF_RenderText_Solid(font, cleanedtext, white); // create text surface
      if (!textsurface) {
        std::cout << "Error loading text surface: " << SDL_GetError()
                  << std::endl;
        return;
      }
      if (linenum++ == focuslineidx) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &linerect);
      } else {
        SDL_SetRenderDrawColor(renderer, 19, 19, 19, 255);
        SDL_RenderFillRect(renderer, &linerect);
      }
      copysurfacetorenderer(textsurface, NULL, &linerect);
      delete[] cleanedtext;
    }
    linerect.y += linerect.h;
  }
}

void window::copysurfacetorenderer(SDL_Surface *surface, SDL_Rect *src,
                                   SDL_Rect *dest) {
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  dest->w = w;
  dest->h = h;
  SDL_RenderCopy(renderer, texture, src, dest);
  SDL_DestroyTexture(texture);
}

void window::renderclear() { SDL_RenderClear(renderer); }

void window::renderpresent() { SDL_RenderPresent(renderer); }

void window::incrementlinefocus() {
  if (focuslineidx + 1 < lines.size()) {
    focuslineidx++;
  }
}

void window::decrementlinefocus() {
  if (focuslineidx - 1 >= 0) {
    focuslineidx--;
  }
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
        /*
      case SDL_KEYDOWN:
        incrementlinefocus();
        std::cout << "key down: " << focuslineidx << std::endl;
        renderclear();
        renderlines();
        renderpresent();
        break;
        */
      case SDL_KEYUP:
        handlekbup(e);
        break;
      case SDL_KEYDOWN:
        handlekbdown(e);
        renderclear();
        renderlines();
        renderpresent();
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
  std::cout << "mode is " << mode << std::endl;
  if (mode == VISUAL) {
    handlekbdownvisualmode(e);
  } else {
    handlekbdowninsertmode(e);
  }
}

void window::handlekbdownvisualmode(SDL_Event e) {
  char c = *SDL_GetKeyName(e.key.keysym.sym);
  if (c == 'J') {
    incrementlinefocus();
    // renderclear();
    // renderlines();
    // renderpresent();
  } else if (c == 'K') {
    decrementlinefocus();
    // renderclear();
    // renderlines();
    // renderpresent();
  } else if (tolower(c) == 'i') {
    mode = INSERT;
    std::cout << "mode change to insert" << std::endl;
  }
}

void window::handlekbdowninsertmode(SDL_Event e) {
  char c;
  switch (e.key.keysym.sym) {
  case SDLK_ESCAPE:
    mode = VISUAL;
    std::cout << "mode change to visual" << std::endl;
    return;
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
    lines[focuslineidx].popchar();
    // renderclear();
    // renderlines();
    // renderpresent();
    return;
  default:
    c = *SDL_GetKeyName(e.key.keysym.sym);
  }
  char cf = cleanchar(c);
  lines[focuslineidx].addchar(cf);
  // renderclear();
  // renderlines();
  // renderpresent();
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

void window::renderemptyscreen() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 19, 19, 19, 255); // red
  SDL_RenderPresent(renderer);
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

SDL_Surface *window::getwindowsurface() { return SDL_GetWindowSurface(win); }

void window::blitsurface(SDL_Surface *src, SDL_Surface *dest) {
  SDL_BlitSurface(src, NULL, dest, NULL);
}

void window::updatewindow() { SDL_UpdateWindowSurface(win); }

void window::resizewindow(int width, int height) {
  SDL_SetWindowSize(win, width, height);
}

void window::movewindow(int x, int y) { SDL_SetWindowPosition(win, x, y); }
