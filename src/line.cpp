#include "line.h"

line::line(std::string text) { this->text = text; }

void line::addchar(char &c) { text += c; }

void line::popchar() {
  if (text.size() > 0)
    text.pop_back();
}

std::string line::gettext() { return text; }
