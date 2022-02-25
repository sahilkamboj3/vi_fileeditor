#include "window.h"

void window::handlekbup(SDL_Event e) {
  switch (e.key.keysym.sym) {
  case SDLK_LSHIFT:
  case SDLK_RSHIFT:
    shiftdown = false;
    break;
  }
}

void window::handletextinput(const char *c) {
  // if (mode == VISUAL) {
  // handletextinputvisualmode(c);
  // return;
  // }
  handletextinputinsertmode(c);
}

void window::handletextinputinsertmode(const char *c) {
  int insertidx = startingletterrenderidx + cursorindex;
  lines[startinglinerenderidx + focuslineidx].addchar(c, insertidx);
  if (cursorindex < charsperline) {
    cursorindex++;
  } else {
    startingletterrenderidx++;
  }
}

void window::handletextinputvisualmode(const char *c) {}

void window::incrementfocusline() {
  if (focuslineidx + 1 < lines.size())
    focuslineidx++;
}

void window::decrementfocusline() {
  if (focuslineidx - 1 >= 0)
    focuslineidx--;
}

void window::setcapslock() {
  if ((SDL_GetModState() & KMOD_CAPS) == KMOD_CAPS)
    capslock = true;
  else
    capslock = false;
}
