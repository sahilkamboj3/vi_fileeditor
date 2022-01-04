#include "window.h"
#include <SDL2/SDL_image.h>

// public functions
window::~window() { destroy(); }

void window::destroy() {
  for (SDL_Surface *image : images) {
    SDL_FreeSurface(image);
  }
}

bool window::init() {
  if (SDL_Init(SDL_INIT_AUDIO)) {
    std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

SDL_Window *window::createwindow() {
  int WIDTH = 640;
  int HEIGHT = 480;
  int X_POS = 0;
  int Y_POS = 0;

  SDL_Window *window = SDL_CreateWindow("Text Editor", X_POS, Y_POS, WIDTH,
                                        HEIGHT, SDL_WINDOW_RESIZABLE);
  if (!window) {
    std::cout << "Creating window failed with error: " << SDL_GetError()
              << std::endl;
    return NULL;
  }

  return window;
}

void window::loadimage(SDL_Window *window, const char *filepath) {
  SDL_Surface *image = loadimagesurface(filepath);
  SDL_Surface *wsurface = getwindowsurface(window);
  blitsurface(image, wsurface);
  updatewindow(window);
}

void window::loadimage(SDL_Window *window, SDL_Surface *image) {
  SDL_Surface *wsurface = getwindowsurface(window);
  blitsurface(image, wsurface);
  updatewindow(window);
}

void window::run(SDL_Window *window) {
  int imagenum = 0;
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        quit = true;
        break;
        /*
      case SDL_MOUSEBUTTONDOWN:
        std::cout << "mouse button click" << std::endl;
        if (++imagenum == images.size()) {
          imagenum = 0;
        }
        loadimage(window, images[imagenum]);
        break;
        */
      }
    }
  }
}

/*
void window::addimage(const char *filepath) {
  images.push_back(IMG_Load(filepath));
}
*/

void window::centerwindow(SDL_Window *window, float resize_relocate_ratio) {
  SDL_Rect rect;
  SDL_GetDisplayBounds(0, &rect);
  int NEW_WIDTH = rect.w * resize_relocate_ratio;
  int NEW_HEIGHT = rect.h * resize_relocate_ratio;
  resizewindow(window, NEW_WIDTH, NEW_HEIGHT);
  movewindow(window, (rect.w - NEW_WIDTH) / 2, (rect.h - NEW_HEIGHT) / 2);
}

// private functions
SDL_Surface *window::loadimagesurface(const char *filepath) {
  return IMG_Load(filepath);
}
SDL_Surface *window::getwindowsurface(SDL_Window *window) {
  return SDL_GetWindowSurface(window);
}

void window::blitsurface(SDL_Surface *src, SDL_Surface *dest) {
  SDL_BlitSurface(src, NULL, dest, NULL);
}

void window::updatewindow(SDL_Window *window) {
  SDL_UpdateWindowSurface(window);
}

void window::resizewindow(SDL_Window *window, int width, int height) {
  SDL_SetWindowSize(window, width, height);
}

void window::movewindow(SDL_Window *window, int x, int y) {
  SDL_SetWindowPosition(window, x, y);
}
