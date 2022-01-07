#include "window.h"

void window::centerwindow(float resize_relocate_ratio) {
  SDL_Rect rect;
  SDL_GetDisplayBounds(0, &rect);
  int NEW_WIDTH = rect.w * resize_relocate_ratio;
  int NEW_HEIGHT = rect.h * resize_relocate_ratio;
  resizewindow(NEW_WIDTH, NEW_HEIGHT);
  movewindow((rect.w - NEW_WIDTH) / 2, (rect.h - NEW_HEIGHT) / 2);
}

void window::setlinesrendering() {
  linesrendering = (windowheight / vimbackgroundheight) - 2;
}

void window::setwindowheightwidth() {
  SDL_GetWindowSize(win, &windowwidth, &windowheight);
}

void window::setvimbackgroundheight() {
  std::string text = "vimbackgroundheight";

  TTF_Font *font = TTF_OpenFont(myfont, fontsize);
  SDL_Color white = {255, 255, 255, 255};
  SDL_Rect linerect;
  linerect.x = 0;
  linerect.y = 0;
  const char *cleanedtext = stringtochar(text);
  SDL_Surface *textsurface =
      TTF_RenderText_Solid(font, cleanedtext, white); // create text surface
  if (!textsurface) {
    std::cout << "Error loading text surface: " << SDL_GetError() << std::endl;
    return;
  }
  delete[] cleanedtext;

  int h;
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textsurface);
  SDL_QueryTexture(texture, NULL, NULL, NULL, &vimbackgroundheight);
  SDL_GetWindowSize(win, NULL, &h);
  SDL_FreeSurface(textsurface);
  SDL_DestroyTexture(texture);
}

void window::resizewindow(int width, int height) {
  SDL_SetWindowSize(win, width, height);
}

void window::movewindow(int x, int y) { SDL_SetWindowPosition(win, x, y); }

SDL_Surface *window::getwindowsurface() { return SDL_GetWindowSurface(win); }

void window::updatewindow() { SDL_UpdateWindowSurface(win); }
