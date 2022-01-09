#include "window.h"

void window::centerwindow(float resize_relocate_ratio) {
  SDL_Rect display;
  SDL_GetDisplayBounds(0, &display);
  int NEW_WIDTH = display.w * resize_relocate_ratio;
  int NEW_HEIGHT = display.h * resize_relocate_ratio;
  resizewindow(NEW_WIDTH, NEW_HEIGHT);
  movewindow((display.w - NEW_WIDTH) / 2, (display.h - NEW_HEIGHT) / 2);
}

void window::resizewindow(int width, int height) {
  SDL_SetWindowSize(win, width, height);
}

void window::movewindow(int x, int y) { SDL_SetWindowPosition(win, x, y); }

void window::setwindowwidthheight() {
  SDL_GetWindowSize(win, &windowwidth, &windowheight);
}

void window::setlineheightandletterwidth() {
  std::string text = "vimbackgroundheight";

  TTF_Font *font = TTF_OpenFont(FONT, FONTSIZE);
  const char *cleanedtext = stringtochar(text);
  SDL_Surface *textsurface = TTF_RenderText_Blended(
      font, cleanedtext,
      (SDL_Color){WHITE.r, WHITE.g, WHITE.b, WHITE.a}); // create text surface
  if (!textsurface) {
    std::cout << "Error loading text surface: " << SDL_GetError() << std::endl;
    return;
  }
  // delete[] cleanedtext;

  int w;
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textsurface);
  SDL_QueryTexture(texture, NULL, NULL, &w, &lineheight);
  letterwidth = w / text.size();
  TTF_CloseFont(font);
  SDL_FreeSurface(textsurface);
  SDL_DestroyTexture(texture);
}
// subtract 4 because first 3 slots taken for rendering line number and
// last slot empty to have 1 empty slot on each side
// [E,LN,E,....E]
void window::setcharsperline() {
  charsperline = (windowwidth / letterwidth) - (linesizedigits + 3);
}

void window::setnumlinesonwindow() {
  numlinesonwindow = (windowheight / lineheight) -
                     2; // to leave space at the bottom to render the vim mode
}

/*
void window::setvimlineletterwidth() {
  vimlineletterwidth = (windowwidth / vimletterwidth) - (linesizedigits + 1) -
                       2; // how many letters fit in a line
}

SDL_Surface *window::getwindowsurface() { return SDL_GetWindowSurface(win); }

void window::updatewindow() { SDL_UpdateWindowSurface(win); }
*/
