#include "window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// public functions
window::window() { win = NULL; }

window::~window() { destroy(); }

void window::destroy() {
  SDL_DestroyWindow(win);
  win = NULL;
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

  return true;
}

void window::loadimage(const char *filepath) {
  SDL_Surface *image = loadimagesurface(filepath);
  SDL_Surface *wsurface = getwindowsurface();
  blitsurface(image, wsurface);
  updatewindow();
}

void window::loadimage(SDL_Surface *image) {
  SDL_Surface *wsurface = getwindowsurface();
  blitsurface(image, wsurface);
  updatewindow();
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
      }
    }
  }
}

void window::centerwindow(float resize_relocate_ratio) {
  SDL_Rect rect;
  SDL_GetDisplayBounds(0, &rect);
  int NEW_WIDTH = rect.w * resize_relocate_ratio;
  int NEW_HEIGHT = rect.h * resize_relocate_ratio;
  resizewindow(NEW_WIDTH, NEW_HEIGHT);
  movewindow((rect.w - NEW_WIDTH) / 2, (rect.h - NEW_HEIGHT) / 2);
}

void window::readfromfile(const char *filepath) {
  SDL_RWops *stream;
  if (!(stream = SDL_RWFromFile(filepath, "rb"))) {
    std::cout << "Error loading file " << filepath << ": " << SDL_GetError()
              << std::endl;
  }
  std::cout << "size: " << SDL_RWsize(stream) << std::endl;
  size_t streamsize = SDL_RWsize(stream);
  char text[streamsize];
  size_t totread = 0, read;
  int times = 0;
  while (totread < streamsize) {
    times++;
    if (!(read = SDL_RWread(stream, text, 1, streamsize - totread)))
      break;
    totread += read;
  }
  std::cout << text << std::endl;
  SDL_FreeRW(stream);
}

// private functions
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
