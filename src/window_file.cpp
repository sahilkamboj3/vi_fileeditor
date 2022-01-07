#include "window.h"

void window::loadfile(std::string filepath) {
  if (!readfromfile(filepath)) {
    return;
  }
  renderclear();
  renderlines();
  rendervimmode();
  renderpresent();
}

bool window::readfromfile(std::string filepath) {
  this->filepath = filepath;
  std::ifstream file(filepath);
  std::string fline;
  int linenum = 1;
  if (file.is_open()) {
    while (getline(file, fline)) {
      line l(fline, linenum++);
      lines.push_back(l);
    }
    file.close();
    return true;
  }
  std::cout << "Error opening file: " << filepath << std::endl;
  return false;
}

void window::writetofile() {
  std::ofstream file(filepath);
  if (file.is_open()) {
    for (line l : lines) {
      std::string text = l.gettext();
      file << text + '\n';
    }
    file.close();
  } else {
    std::cout << "Error writing back to file " << filepath << std::endl;
  }
}
