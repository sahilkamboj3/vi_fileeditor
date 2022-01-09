#include "window.h"

void window::renderclear() { SDL_RenderClear(renderer); }

void window::renderpresent() { SDL_RenderPresent(renderer); }

void window::renderemptyscreen() {
  renderclear();
  SDL_SetRenderDrawColor(renderer, DARKGREY.r, DARKGREY.g, DARKGREY.b,
                         DARKGREY.a);
  renderpresent();
}

void window::rendercursor() {
  SDL_Rect crect;
  crect.x = (linesizedigits + 2 + cursorindex) * letterwidth;
  crect.y = focuslineidx * lineheight;
  if (mode == VISUAL)
    crect.w = letterwidth;
  else
    crect.w = letterwidth / 5;
  crect.h = lineheight;
  SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a);
  SDL_RenderFillRect(renderer, &crect);
}

void window::rendervimmode() {
  TTF_Font *font = TTF_OpenFont(FONT, FONTSIZE);
  SDL_Rect lrect;
  lrect.x = letterwidth;
  lrect.y = windowheight - lineheight;
  std::string text;
  const char *cleanedtext;
  if (mode == VISUAL) {
    text = "VISUAL";
  } else {
    text = "INSERT";
  }
  cleanedtext = stringtochar(text);
  SDL_Surface *textsurface = TTF_RenderText_Blended(font, cleanedtext,
                                                    RED); // create text surface
  if (!textsurface) {
    std::cout << "Error loading text surface: " << SDL_GetError() << std::endl;
    return;
  }
  SDL_SetRenderDrawColor(renderer, DARKGREY.r, DARKGREY.g, DARKGREY.b,
                         DARKGREY.a);
  SDL_RenderFillRect(renderer, &lrect);
  copysurfacetorenderer(textsurface, NULL, &lrect);
  TTF_CloseFont(font);
}

void window::renderlineletterslot() {
  TTF_Font *font = TTF_OpenFont(FONT, FONTSIZE);
  std::string text = getfilenamefromfilepath(filepath) + ":" +
                     inttostring(startinglinerenderidx + focuslineidx + 1) +
                     "," +
                     inttostring(startingletterrenderidx + cursorindex + 1);
  SDL_Rect lrect;
  lrect.x = windowwidth - ((text.size() + 1) * letterwidth);
  lrect.y = windowheight - lineheight;
  const char *cleanedtext = stringtochar(text);
  SDL_Surface *textsurface = TTF_RenderText_Blended(font, cleanedtext,
                                                    RED); // create text surface
  if (!textsurface) {
    std::cout << "Error loading text surface: " << SDL_GetError() << std::endl;
    return;
  }
  SDL_SetRenderDrawColor(renderer, DARKGREY.r, DARKGREY.g, DARKGREY.b,
                         DARKGREY.a);
  SDL_RenderFillRect(renderer, &lrect);
  copysurfacetorenderer(textsurface, NULL, &lrect);
  TTF_CloseFont(font);
}

void window::renderlines() {
  linesizedigits = getnumdigits(lines.size());
  rendercursor();

  // set up SDL_Rect for line and line numbers
  TTF_Font *font = TTF_OpenFont(FONT, FONTSIZE);
  SDL_Rect lnrect, lrect;
  lnrect.x = letterwidth;
  lnrect.y = 0;
  lnrect.w = linesizedigits * letterwidth;
  lnrect.h = lineheight;

  lrect.x = (1 + linesizedigits + 1) * letterwidth;
  lrect.y = 0;
  lrect.h = lineheight;

  int lineidx = 0;
  int endidx;
  // check this
  if (startinglinerenderidx || (lines.size() > numlinesonwindow)) {
    endidx = startinglinerenderidx + numlinesonwindow;
  } else {
    endidx = lines.size();
  }

  for (int i = startinglinerenderidx; i < endidx; i++) {
    // handle line number
    int linenum = i + 1;
    const char *cleanedlinenum = inttochar(linenum);
    SDL_Surface *lnsurface =
        TTF_RenderText_Blended(font, cleanedlinenum,
                               WHITE); // create text surface
    if (!lnsurface) {
      std::cout << "Error loading line number surface: " << SDL_GetError()
                << std::endl;
      return;
    }
    copysurfacetorenderer(lnsurface, NULL, &lnrect);

    // handle text
    std::string text = lines[i].gettext(startingletterrenderidx, charsperline);
    if (text.size() > 0) {
      const char *cleanedtext = stringtochar(text);
      SDL_Surface *textsurface =
          TTF_RenderText_Blended(font, cleanedtext,
                                 WHITE); // create text surface
      if (!textsurface) {
        std::cout << "Error loading text surface: " << SDL_GetError()
                  << std::endl;
        return;
      }

      copysurfacetorenderer(textsurface, NULL, &lrect);
    }
    lineidx++;
    lrect.y += lrect.h; // lrect.h should equal lineheight
    lnrect.y += lrect.h;
  }
  TTF_CloseFont(font);

  renderlineletterslot();
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

/*
void window::blitsurface(SDL_Surface *src, SDL_Surface *dest) {
  SDL_BlitSurface(src, NULL, dest, NULL);
}
*/
