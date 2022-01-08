#include "window.h"

void window::handlekbup(SDL_Event e) {
  switch (e.key.keysym.sym) {
  case SDLK_LSHIFT:
  case SDLK_RSHIFT:
    shiftdown = false;
    break;
  case SDLK_COLON:
    std::cout << "Colon key lifted" << std::endl;
    break;
  }
}

void window::handlekbdown(SDL_Event e) {
  if (mode == VISUAL) {
    handlekbdownvisualmode(e);
  } else {
    handlekbdowninsertmode(e);
  }
}

void window::handlekbdownvisualmode(SDL_Event e) {
  char c = *SDL_GetKeyName(e.key.keysym.sym);

  if (c == 'J') {
    if (lines.size() < linesrendering) {
      incrementlinefocus();
    } else if (focuslineidx < linesrendering - 1) {
      focuslineidx++;
    } else if (linerenderstartidx + linesrendering < lines.size()) {
      linerenderstartidx++;
    }
  } else if (c == 'K') {
    if (focuslineidx == 0 && linerenderstartidx > 0) {
      linerenderstartidx--;
    } else {
      decrementlinefocus();
    }
  } else if (tolower(c) == 'i') {
    mode = INSERT;
  } else if (c == 'L') {
    if (vimcursorstartidx + 1 < vimlineletterwidth) {
      vimcursorstartidx++;
    } else {
      letterrenderstartidx++;
    }
  } else if (c == 'H') {
    if (vimcursorstartidx == 0 && letterrenderstartidx > 0) {
      letterrenderstartidx--;
    } else {
      vimcursorstartidx--;
    }
  }
}

void window::handlekbdowninsertmode(SDL_Event e) {
  char c;
  std::string cs;
  switch (e.key.keysym.sym) {
  case SDLK_ESCAPE:
    mode = VISUAL;
    return;
  case SDLK_RSHIFT:
  case SDLK_LSHIFT:
    shiftdown = true;
    return;
  case SDLK_TAB:
    for (int i = 0; i < tabtospace; i++)
      cs += " ";
    break;
  case SDLK_CAPSLOCK:
    capslock = !capslock;
    return;
  case SDLK_SPACE:
    c = ' ';
    break;
  case SDLK_KP_ENTER:
    c = '\n';
    break;
  case SDLK_BACKSPACE:
    lines[linerenderstartidx + focuslineidx].popchar();
    return;
  default:
    c = *SDL_GetKeyName(e.key.keysym.sym);
  }
  if (cs.size())
    lines[linerenderstartidx + focuslineidx].addstr(cs);
  else {
    char cf = cleanchar(c);
    lines[linerenderstartidx + focuslineidx].addchar(cf);
  }
}

char window::cleanchar(char c) {
  if (c == '\n')
    return c;
  if (c >= 'A' && c <= 'Z') {
    if (capslock | shiftdown)
      return toupper(c);
    return tolower(c);
  }
  if (c == ' ' || !shiftdown) {
    return c;
  }
  return shift_x_pairs[c];
}

// private functions
void window::incrementlinefocus() {
  if (focuslineidx + 1 < lines.size()) { // check here
    focuslineidx++;
  }
}

void window::decrementlinefocus() {
  if (focuslineidx - 1 >= 0) {
    focuslineidx--;
  }
}

std::string window::chartostring(const char *cstr) {
  std::string str(cstr);
  return str;
}

const char *window::stringtochar(std::string str) {
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  return cstr;
}
