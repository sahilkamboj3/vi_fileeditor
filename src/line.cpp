#include "line.h"

line::line(std::string text, int linenum) {
  this->text = text;
  this->linenum = linenum;
}
void line::addchar(char &c) { text += c; }

void line::addstr(std::string &s) { text += s; }

void line::popchar() {
  if (text.size() > 0)
    text.pop_back();
}

std::string line::gettext() { return text; }

int line::getlinenum() { return linenum; }
