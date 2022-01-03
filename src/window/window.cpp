#include "window.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace window {
void Window::Run() {
  //  uint32_t DELAY = 5 * 1000;
  uint32_t WIDTH = 680;
  uint32_t HEIGHT = 480;
  uint32_t X_POS = 50;
  uint32_t Y_POS = 50;

  if (!_Init()) {
    std::cout << "Failed to initialize window..." << std::endl;
    return;
  }

  SDL_Window *win = SDL_CreateWindow("Text Editor", X_POS, Y_POS, WIDTH, HEIGHT,
                                     SDL_WINDOW_RESIZABLE);
  if (!win) {
    std::cout << "Cannot create editor...";
    return;
  }

  _CreateSurface(win);

  // SDL_Delay(DELAY);
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN) ||
          (e.type == SDL_MOUSEBUTTONDOWN)) {
        quit = true;
      }
    }
  }

  _Destroy(win);
}

void Window::RunPythonScript(const std::string &filepath) {
  std::string command = "python " + filepath;
  system(command.c_str());
}

bool Window::_Init() {
  return SDL_Init(SDL_INIT_VIDEO) == 0; // true = success, else false
}

void Window::_CreateSurface(SDL_Window *&window) {
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  if (!surface) {
    std::cout << "Failed to get surface..." << std::endl;
    return;
  }
  SDL_UpdateWindowSurface(window);
}

void Window::_Destroy(SDL_Window *&window) {
  SDL_DestroyWindow(window);
  SDL_Quit();
}

} // namespace window
