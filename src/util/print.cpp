#include "print.h"

namespace util {

void Print::printStringVector(const std::vector<std::string> &v) {
  std::cout << "[";
  for (size_t i = 0; i < v.size(); i++) {
    const std::string &s = v[i];
    std::cout << s;
    if (i < v.size() - 1) {
      std::cout << " ";
    }
  }
  std::cout << "]" << std::endl;
}
} // namespace util
