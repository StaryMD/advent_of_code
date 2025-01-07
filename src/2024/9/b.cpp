#include <array>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <string>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 9, 'B'>(std::stringstream input) {
  struct File {
    int id;
    int size;
  };

  const std::string line = input.str();

  std::deque<File> files;

  for (int i = 0; i < line.size(); ++i) {
    const int id = ((i & 1)) ? -1 : (i / 2);
    files.emplace_back(id, line[i] - '0');
  }

  std::array<int, 10> min_start_pos = {0};

  for (int right = files.size() - 1; right > 0; --right) {
    if (files[right].id != -1) {
      int &left = min_start_pos[files[right].size];

      for (; left < right; ++left) {
        if (files[left].id == -1 && files[right].size <= files[left].size) {
          const File file = files[right];

          files[left].size -= files[right].size;
          files[right].id = -1;
          files.pop_back();
          files.insert(files.begin() + left, file);
          break;
        }
      }
    }
  }

  uint64_t points = 0;
  int decomp_counter = 0;

  for (int i = 0; i < files.size(); ++i) {
    for (int j = 0; j < files[i].size; ++j) {
      if (files[i].id != -1) {
        points += files[i].id * decomp_counter;
      }
      ++decomp_counter;
    }
  }

  return std::to_string(points);
}
