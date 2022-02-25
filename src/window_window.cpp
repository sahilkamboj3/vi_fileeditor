#include "window.h"

int window::getdisplaywidth() {
  SDL_DisplayMode dm;
  SDL_GetCurrentDisplayMode(0, &dm);
  return dm.w;
}

int window::getdisplayheight() {
  SDL_DisplayMode dm;
  SDL_GetCurrentDisplayMode(0, &dm);
  return dm.h;
}

void window::setlineheightandletterwidth() {
  std::string text = "vimbackgroundheight";

  TTF_Font *font = TTF_OpenFont(FONT, FONTSIZE);
  const char *cleanedtext = stringtochar(text);
  SDL_Surface *textsurface =
      TTF_RenderText_Blended(font, cleanedtext,
                             WHITE); // create text surface

  if (textsurface) {
    int textwidth;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_QueryTexture(texture, NULL, NULL, &textwidth, &lineheight);
    letterwidth = textwidth / text.size();
    SDL_DestroyTexture(texture);
  } else {
    std::cout << "Error loading text surface: " << SDL_GetError() << std::endl;
  }

  // delete[] cleanedtext;
  TTF_CloseFont(font);
  SDL_FreeSurface(textsurface);
}

// subtract 3 because first 3 slots taken for rendering line number and
// last slot empty to have 1 empty slot on each side
// [E,LN,T,T,...E]
void window::setcharsperline() {
  charsperline = (WINDOW_WIDTH / letterwidth) - (numlinedigits + 3);
}

// E
// T
// T
// ...
// E
void window::setnumlinesonwindow() {
  numlinesonwindow = (WINDOW_HEIGHT / lineheight) -
                     2; // to leave space at the bottom to render the vim mode
}
