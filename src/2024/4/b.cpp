#include <array>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 4, 'B'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  const int size_y = lines.size();
  const int size_x = lines[0].size();

  int points = 0;

  for (int y = 1; y < size_y - 1; ++y) {
    for (int x = 1; x < size_x - 1; ++x) {
      if (lines[y][x] == 'A') {
        const char str[5] = {
            lines[y - 1][x - 1],
            lines[y - 1][x + 1],
            lines[y + 1][x + 1],
            lines[y + 1][x - 1],
            '\0',
        };

        if (strcmp(str, "MMSS") == 0 || strcmp(str, "MSSM") == 0 || strcmp(str, "SSMM") == 0 ||
            strcmp(str, "SMMS") == 0) {
          ++points;
        }
      }
    }
  }

  return std::to_string(points);
}
