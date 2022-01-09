#include "window.h"

std::string window::chartostring(const char *cstr) {
  std::string str(cstr);
  return str;
}

const char *window::stringtochar(std::string &str) {
  // char *cstr = new char[str.length() + 1];
  // strcpy(cstr, str.c_str());
  // return cstr;
  return str.c_str();
}

std::string window::inttostring(int num) { return std::to_string(num); }

const char *window::inttochar(int num) {
  std::string numstr = std::to_string(num);
  const char *cleanednum = stringtochar(numstr);
  return cleanednum;
}

std::string window::getfilenamefromfilepath(std::string filepath) {
  size_t pos = filepath.size() - 1;
  char SLASH = '/';
  while (pos && filepath[pos] != SLASH) {
    pos--;
  }
  return filepath.substr(pos + 1);
}

int window::getnumdigits(int num) { return log10(num) + 1; }
