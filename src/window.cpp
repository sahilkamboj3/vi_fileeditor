#include "window.h"

// public functions
window::window() {
  win = nullptr;
  renderer = nullptr;
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
  // delete[] FONT;
  win = nullptr;
  renderer = nullptr;
}

bool window::init() {
  int WIDTH = 640;
  int HEIGHT = 480;
  int X_POS = 0;
  int Y_POS = 0;

  win = SDL_CreateWindow("File Editor", X_POS, Y_POS, WIDTH, HEIGHT,
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
  centerwindow(0.75);
  setwindowwidthheight();
  setlineheightandletterwidth();
  setnumlinesonwindow();
  renderemptyscreen();
  mode = VISUAL;
  return true;
}

void window::loadfile(std::string filepath) {
  if (!readfromfile(filepath)) {
    return;
  }
  setcharsperline();
  renderclear();
  renderlines();
  rendervimmode();
  renderpresent();
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
        renderclear();
        renderlines();
        rendervimmode();
        renderpresent();
        break;
      }
    }
  }
}
