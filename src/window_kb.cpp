#include "window.h"

void window::handlekbup(SDL_Event e) {
  switch (e.key.keysym.sym) {
  case SDLK_LSHIFT:
  case SDLK_RSHIFT:
    shiftdown = false;
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

  switch (e.key.keysym.sym) {
  case SDLK_LSHIFT:
  case SDLK_RSHIFT:
    shiftdown = true;
    return;
  case SDLK_0:
    cursorindex = 0;
    startingletterrenderidx = 0;
    return;
  case SDLK_4:
    std::string text = lines[startinglinerenderidx + focuslineidx].gettext();
    if (shiftdown) {
      if (text.size() >= charsperline) {
        cursorindex = charsperline - 1;
        startingletterrenderidx = text.size() - charsperline;
      } else {
        cursorindex = text.size() - 1;
        startingletterrenderidx = 0;
      }
    }
  }

  if (c == 'J') { // modify focuslineidx
    if (lines.size() < numlinesonwindow)
      incrementfocusline();
    // at this point, lines.size() == numlinesonwindow
    else if (focuslineidx < numlinesonwindow - 1)
      focuslineidx++;
    else if (startinglinerenderidx + numlinesonwindow < lines.size())
      startinglinerenderidx++;

  } else if (c == 'K') {
    if (focuslineidx == 0 && startinglinerenderidx > 0) {
      startinglinerenderidx--;
    } else {
      decrementfocusline();
    }

  } else if (tolower(c) == 'i') {
    mode = INSERT;

  } else if (c == 'L') {
    std::string text = lines[startinglinerenderidx + focuslineidx].gettext();
    if (cursorindex == charsperline - 1) { // cursor at the end of line
      if (startingletterrenderidx + charsperline < text.size()) {
        startingletterrenderidx++;
      }
    } else { // cursor somewhere in the middle
      if (startingletterrenderidx) {
        cursorindex++;
      } else if (cursorindex < text.size() - 1) { // startingletterrenderidx = 0
        cursorindex++;
      }
    }

  } else if (c == 'H') {
    if (cursorindex == 0 && startingletterrenderidx > 0) {
      startingletterrenderidx--;
    } else if (cursorindex > 0) {
      cursorindex--;
    }

  } else if (shiftdown && c == 'A') {
    mode = INSERT;
    std::string text = lines[startinglinerenderidx + focuslineidx].gettext();
    if (text.size() >= startingletterrenderidx + charsperline) {
      cursorindex = charsperline;
      startingletterrenderidx = std::max(0, (int)text.size() - charsperline);
    } else {
      cursorindex = (int)text.size() - startingletterrenderidx;
    }
    return;
  }

  std::string text = lines[startinglinerenderidx + focuslineidx].gettext();
  if (text.size() == 0) {
    cursorindex = 0;
    startingletterrenderidx = 0;
  } else if (startingletterrenderidx + cursorindex >= text.size()) {
    if (startingletterrenderidx >= text.size())
      startingletterrenderidx = std::max(0, (int)text.size() - charsperline);
    cursorindex =
        std::min((int)text.size() - startingletterrenderidx - 1, charsperline);
  }
}

void window::handlekbdowninsertmode(SDL_Event e) {
  char c;
  std::string cs;
  switch (e.key.keysym.sym) {
  case SDLK_ESCAPE:
    mode = VISUAL;
    if (lines[startinglinerenderidx + focuslineidx].gettext().size() == 0) {
      cursorindex = 0;
      startingletterrenderidx = 0;
    } else if (startingletterrenderidx + cursorindex ==
               lines[startinglinerenderidx + focuslineidx].gettext().size())
      cursorindex--;
    else
      cursorindex = std::min(cursorindex, charsperline - 1);
    return;
  case SDLK_RSHIFT:
  case SDLK_LSHIFT:
    shiftdown = true;
    return;
  case SDLK_TAB:
    for (int i = 0; i < TABTOSPACE; i++)
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
    if (startingletterrenderidx + cursorindex) {
      lines[startinglinerenderidx + focuslineidx].popchar(
          startingletterrenderidx + cursorindex - 1);
      if (!cursorindex) {
        lines[startinglinerenderidx + focuslineidx].popchar();
        if (startingletterrenderidx - 1 >= 0)
          startingletterrenderidx--;
        return;
      } else { // if (cursorindex && (cursorindex < charsperline)) {
        cursorindex--;
      }
    }
    return;
  default:
    c = *SDL_GetKeyName(e.key.keysym.sym);
  }
  // handle separately
  if (cs.size()) {
    if (cursorindex + TABTOSPACE < charsperline) {
      lines[startinglinerenderidx + focuslineidx].addstr(
          cs, startingletterrenderidx + cursorindex);
      cursorindex += TABTOSPACE;
    } else {
      lines[startinglinerenderidx + focuslineidx].addstr(
          cs, startingletterrenderidx + cursorindex);
      startingletterrenderidx += TABTOSPACE;
    }

  } else {
    char cf = cleanchar(c);
    if (cursorindex < charsperline) {
      lines[startinglinerenderidx + focuslineidx].addchar(
          cf, startingletterrenderidx + cursorindex);
      cursorindex++;
    } else {
      lines[startinglinerenderidx + focuslineidx].addchar(
          cf, startingletterrenderidx + cursorindex);
      startingletterrenderidx++;
    }
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
void window::incrementfocusline() {
  if (focuslineidx + 1 < lines.size())
    focuslineidx++;
}

void window::decrementfocusline() {
  if (focuslineidx - 1 >= 0)
    focuslineidx--;
}
