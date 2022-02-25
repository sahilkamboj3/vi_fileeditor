#include "window.h"

// public functions
window::window() {
  win = nullptr;
  renderer = nullptr;
}

window::~window() { destroy(); }

void window::destroy() {
  writetofile();
  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(renderer);
  win = nullptr;
  renderer = nullptr;
}

bool window::init() {
  int X_POS = (getdisplaywidth() - WINDOW_WIDTH) / 2;
  int Y_POS = (getdisplayheight() - WINDOW_HEIGHT) / 2;

  // initialize window
  win = SDL_CreateWindow("File Editor", X_POS, Y_POS, WINDOW_WIDTH,
                         WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
  if (!win) {
    std::cout << "Creating window failed with error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  renderer = SDL_CreateRenderer(win, -1, 0);
  if (!renderer) {
    std::cout << "Creating renderer failed with error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  // initialize window settings
  setlineheightandletterwidth();
  setnumlinesonwindow();
  setcharsperline();
  setcapslock();
  mode = VISUAL;

  return true;
}

bool window::loadfile(std::string filepath) { return readfromfile(filepath); }

void window::run() {
  SDL_Event e;
  bool quit = false;
  SDL_StartTextInput();

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      uint32_t begin, end;
      begin = SDL_GetTicks();

      switch (e.type) {
      case SDL_QUIT:
        quit = true;
        end = SDL_GetTicks();
        break;
      case SDL_KEYUP: {
        handlekbup(e);
        end = SDL_GetTicks();
        break;
      }
      case SDL_TEXTINPUT: {
        handletextinput(e.text.text);
        renderclear();
        end = SDL_GetTicks();
        break;
      }
        /*
        case SDL_KEYDOWN: {
          handlekbdown(e);
          renderclear();
          renderlines();
          rendervimmode();
          renderpresent();
          end = SDL_GetTicks();
          break;
        }
        */
      }

      int diff = end - begin;
      if (diff < FRAMERATE) {
        SDL_Delay(FRAMERATE - diff);
      }
    }
  }
}
