#include <array>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 4, 'A'>(std::stringstream input) {
  constexpr std::array<std::pair<int, int>, 8> dirs = {
      std::make_pair(0, 1),  std::make_pair(1, 1),   std::make_pair(1, 0),  std::make_pair(1, -1),
      std::make_pair(0, -1), std::make_pair(-1, -1), std::make_pair(-1, 0), std::make_pair(-1, 1),
  };

  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  const int size_y = lines.size();
  const int size_x = lines[0].size();

  int points = 0;

  for (const auto [dy, dx] : dirs) {
    for (int y = 0; y < size_y; ++y) {
      if ((0 <= y + 3 * dy) && (y + 3 * dy < size_y)) {
        for (int x = 0; x < size_x; ++x) {
          if ((0 <= x + 3 * dx) && (x + 3 * dx < size_x)) {
            if (lines[y + 0 * dy][x + 0 * dx] == 'X' && lines[y + 1 * dy][x + 1 * dx] == 'M' &&
                lines[y + 2 * dy][x + 2 * dx] == 'A' && lines[y + 3 * dy][x + 3 * dx] == 'S') {
              ++points;
            }
          }
        }
      }
    }
  }

  return std::to_string(points);
}
