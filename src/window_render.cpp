#include "window.h"

void window::renderlines() {
  if (!lines.size()) {
    renderemptyscreen();
    return;
  }

  TTF_Font *font = TTF_OpenFont(myfont, fontsize);
  SDL_Color white = {255, 255, 255, 255};
  SDL_Rect linerect;
  linerect.x = 0;
  linerect.y = 0;
  int w;
  SDL_GetWindowSize(win, &w, NULL);
  int linenum = 0;
  int endidx;
  if (linerenderstartidx || (lines.size() > linesrendering)) {
    endidx = linerenderstartidx + linesrendering;
  } else {
    endidx = lines.size();
  }

  for (int i = linerenderstartidx; i < endidx; i++) {
    std::string text = lines[i].gettext();
    if (text.size() > 0) {
      const char *cleanedtext = stringtochar(text);
      SDL_Surface *textsurface =
          TTF_RenderText_Solid(font, cleanedtext, white); // create text surface
      if (!textsurface) {
        std::cout << "Error loading text surface: " << SDL_GetError()
                  << std::endl;
        return;
      }
      linerect.w = w;
      linerect.h = vimbackgroundheight;
      if (linenum == focuslineidx) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &linerect);
      } else {
        SDL_SetRenderDrawColor(renderer, 19, 19, 19, 255);
        SDL_RenderFillRect(renderer, &linerect);
      }
      copysurfacetorenderer(textsurface, NULL, &linerect);
      delete[] cleanedtext;
      linenum++;
    }
    linerect.y += linerect.h;
  }
  TTF_CloseFont(font);
}

void window::rendervimmode() {
  TTF_Font *font = TTF_OpenFont(myfont, fontsize);
  SDL_Color red = {255, 0, 0, 255};
  SDL_Rect linerect;
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  linerect.x = 0;
  linerect.y = h - vimbackgroundheight;
  const char *cleanedtext;
  if (mode == VISUAL) {
    cleanedtext = stringtochar("VISUAL");
  } else {
    cleanedtext = stringtochar("INSERT");
  }
  SDL_Surface *textsurface =
      TTF_RenderText_Solid(font, cleanedtext, red); // create text surface
  if (!textsurface) {
    std::cout << "Error loading text surface: " << SDL_GetError() << std::endl;
    return;
  }
  SDL_SetRenderDrawColor(renderer, 19, 19, 19, 255);
  linerect.w = w;
  SDL_RenderFillRect(renderer, &linerect);
  copysurfacetorenderer(textsurface, NULL, &linerect);
  delete[] cleanedtext;
  TTF_CloseFont(font);
}

void window::copysurfacetorenderer(SDL_Surface *surface, SDL_Rect *src,
                                   SDL_Rect *dest) {
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  dest->w = w;
  dest->h = h;
  SDL_RenderCopy(renderer, texture, src, dest);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void window::renderclear() { SDL_RenderClear(renderer); }

void window::renderpresent() { SDL_RenderPresent(renderer); }

void window::renderemptyscreen() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 19, 19, 19, 255); // darkgrey
  SDL_RenderPresent(renderer);
}

void window::blitsurface(SDL_Surface *src, SDL_Surface *dest) {
  SDL_BlitSurface(src, NULL, dest, NULL);
}
