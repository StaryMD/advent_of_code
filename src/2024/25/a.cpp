#include <algorithm>
#include <string>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 25, 'A'>(std::stringstream input) {
  std::vector<std::string> lines;

  int empty_lines_count = 0;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);

    empty_lines_count += line.empty();
  }

  const int lock_height = lines.size() / (empty_lines_count + 1);
  const int lock_width = lines[0].size();

  std::vector<std::vector<int>> keys;
  std::vector<std::vector<int>> locks;

  std::vector<int> counters(lock_width);

  for (int chunk_y = 0; chunk_y < lines.size(); chunk_y += lock_height + 1) {
    std::ranges::fill(counters, 0);

    for (int y = 0; y < lock_height; ++y) {
      for (int x = 0; x < lock_width; ++x) {
        if (lines[chunk_y + y][x] == '#') {
          ++counters[x];
        }
      }
    }

    if (lines[chunk_y][0] == '.') {
      keys.push_back(counters);
    } else {
      locks.push_back(counters);
    }
  }

  int points = 0;

  for (const std::vector<int> &key : keys) {
    for (const std::vector<int> &lock : locks) {
      bool good = true;

      for (int i = 0; i < lock_width; ++i) {
        if (key[i] + lock[i] > 7) {
          good = false;
        }
      }

      points += good;
    }
  }

  return std::to_string(points);
}
