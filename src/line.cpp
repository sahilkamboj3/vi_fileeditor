#include "line.h"

line::line() : text("") {}

line::line(std::string text) { this->text = text; }

void line::addchar(char &c) { text += c; }

void line::addchar(char &c, size_t idx) { text.insert(idx, std::string(1, c)); }

void line::addstr(std::string &s) { text += s; }

void line::addstr(std::string &s, size_t idx) { text.insert(idx, s); }

void line::popchar() {
  if (text.size() > 0)
    text.pop_back();
}

void line::popchar(size_t idx) { text.erase(idx, 1); }

void line::removestr(int idx) { text.erase(idx); }

std::string line::gettext() { return text; }

std::string line::gettext(int start) { return text.substr(start); }

std::string line::gettext(int start, int length) {
  if (start >= text.size())
    return "";
  return text.substr(start, length);
}

line &line::operator=(const line &other) {
  text = other.text;
  return *this;
}
