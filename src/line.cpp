#include "line.h"

line::line(int linenum) {
  this->text = "";
  this->linenum = linenum;
}

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

std::string line::gettext(int start, int length) {
  if (start >= text.size())
    return "";
  return text.substr(start, length);
}

int line::getlinenum() { return linenum; }
