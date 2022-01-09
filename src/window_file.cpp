#include "window.h"

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
    if (!lines.size()) {
      line l(1);
      lines.push_back(l);
    }
    linesizedigits = log10(lines.size()) + 1;
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
    return;
  }
  std::cout << "Error writing back to file " << filepath << std::endl;
}
