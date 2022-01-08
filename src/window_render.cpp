#include "window.h"

void window::rendercursor() {
  SDL_Rect crect;
  crect.x = ((linenumdigits + 1 + vimcursorstartidx) * vimletterwidth) + 5;
  crect.y = focuslineidx * vimbackgroundheight;
  crect.w = vimletterwidth; // w;
  crect.h = vimbackgroundheight;
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer, &crect);
}

void window::renderlines() {
  if (!lines.size()) {
    renderemptyscreen();
    return;
  }

  rendercursor();

  TTF_Font *font = TTF_OpenFont(myfont, fontsize);
  SDL_Color white = {255, 255, 255, 255};

  SDL_Rect lnrect;
  lnrect.x = 5;
  lnrect.y = 0;

  SDL_Rect lrect;
  lrect.x = (linenumdigits + 1) * vimletterwidth + lnrect.x;
  lrect.y = 0;

  int w;
  SDL_GetWindowSize(win, &w, NULL);
  int lineidx = 0;
  int endidx;
  if (linerenderstartidx || (lines.size() > linesrendering)) {
    endidx = linerenderstartidx + linesrendering;
  } else {
    endidx = lines.size();
  }

  for (int i = linerenderstartidx; i < endidx; i++) {
    // std::string text = lines[i].gettext();
    std::string text =
        lines[i].gettext(letterrenderstartidx, vimlineletterwidth);

    // handle line number
    int linenum = lines[i].getlinenum();
    std::string linenumstr = std::to_string(linenum);
    const char *cleanedlinenum = stringtochar(linenumstr);
    SDL_Surface *lnsurface = TTF_RenderText_Blended(
        font, cleanedlinenum, white); // create text surface
    if (!lnsurface) {
      std::cout << "Error loading line number surface: " << SDL_GetError()
                << std::endl;
      return;
    }
    copysurfacetorenderer(lnsurface, NULL, &lnrect);
    delete[] cleanedlinenum;

    if (text.size() > 0) {
      // handle text
      const char *cleanedtext = stringtochar(text);
      SDL_Surface *textsurface = TTF_RenderText_Blended(
          font, cleanedtext, white); // create text surface
      if (!textsurface) {
        std::cout << "Error loading text surface: " << SDL_GetError()
                  << std::endl;
        return;
      }

      copysurfacetorenderer(textsurface, NULL, &lrect);
      delete[] cleanedtext;
    }
    lineidx++;
    lrect.y += lrect.h;
    lnrect.y += lrect.h;
  }
  TTF_CloseFont(font);
}

void window::rendervimmode() {
  TTF_Font *font = TTF_OpenFont(myfont, fontsize);
  SDL_Color red = {255, 0, 0, 255};
  SDL_Rect lrect;
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  lrect.x = 0;
  lrect.y = h - vimbackgroundheight;
  const char *cleanedtext;
  if (mode == VISUAL) {
    cleanedtext = stringtochar("VISUAL");
  } else {
    cleanedtext = stringtochar("INSERT");
  }
  SDL_Surface *textsurface =
      TTF_RenderText_Blended(font, cleanedtext, red); // create text surface
  if (!textsurface) {
    std::cout << "Error loading text surface: " << SDL_GetError() << std::endl;
    return;
  }
  SDL_SetRenderDrawColor(renderer, 38, 38, 38, 255);
  lrect.w = w;
  SDL_RenderFillRect(renderer, &lrect);
  copysurfacetorenderer(textsurface, NULL, &lrect);
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
  SDL_SetRenderDrawColor(renderer, 38, 38, 38, 255); // darkgrey
  SDL_RenderPresent(renderer);
}

void window::blitsurface(SDL_Surface *src, SDL_Surface *dest) {
  SDL_BlitSurface(src, NULL, dest, NULL);
}
