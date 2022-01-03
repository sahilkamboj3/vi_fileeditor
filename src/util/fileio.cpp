#include "fileio.h"
#include <fstream>
#include <iostream>

namespace util {
std::vector<std::string> *FileIO::readFile(const std::string &filename) {
  std::ifstream file(filename);
  std::vector<std::string> *content = new std::vector<std::string>();
  std::string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      content->push_back(line);
    }
  }
  return content;
}

void FileIO::writeToFile(const std::vector<std::string> &vec) {
  std::ofstream file;
  file.open("out.txt");
  for (const std::string &s : vec) {
    file << s + '\n';
  }
  file.close();
}

} // namespace util
