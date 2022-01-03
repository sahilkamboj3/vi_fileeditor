#pragma once
#include <string>
#include <vector>

namespace util {
class FileIO {
public:
  std::vector<std::string> *readFile(const std::string &filename);
  void writeToFile(const std::vector<std::string> &vec);
};
} // namespace util
