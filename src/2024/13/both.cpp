#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day13_2024 {

std::string SolveHelper(std::stringstream &input, const int64_t offset) {
  int64_t points = 0;

  while (input) {
    std::vector<std::string> lines;

    for (int i = 0; i < 4; ++i) {
      lines.emplace_back();
      std::getline(input, lines.back());
    }

    const int a_x = (lines[0][12] - '0') * 10 + lines[0][13] - '0';
    const int a_y = (lines[0][18] - '0') * 10 + lines[0][19] - '0';

    const int b_x = (lines[1][12] - '0') * 10 + lines[1][13] - '0';
    const int b_y = (lines[1][18] - '0') * 10 + lines[1][19] - '0';

    int64_t p_x = 0;
    int64_t p_y = 0;

    int i = 9;
    while (lines[2][i] != ',') {
      p_x = p_x * 10 + lines[2][i] - '0';
      i++;
    }

    i += 4;
    while (i != lines[2].size()) {
      p_y = p_y * 10 + lines[2][i] - '0';
      i++;
    }

    p_x += offset;
    p_y += offset;

    const int64_t x_sus = b_x * p_y - b_y * p_x;
    const int64_t x_jos = b_x * a_y - b_y * a_x;

    int32_t best = -1;

    if (x_sus % x_jos == 0) {
      const int64_t x = x_sus / x_jos;

      const int64_t y1 = (p_x - x * a_x) / b_x;
      const int64_t y2 = (p_y - x * a_y) / b_y;

      if (y1 == y2 and x * a_x + y1 * b_x == p_x and x * a_y + y1 * b_y == p_y) {
        points += x * 3 + y1;
      }
    }
  }

  return std::to_string(points);
}

}  // namespace day13_2024

template <>
std::string Solve<2024, 13, 'A'>(std::stringstream input) {
  return day13_2024::SolveHelper(input, 0);
}

template <>
std::string Solve<2024, 13, 'B'>(std::stringstream input) {
  return day13_2024::SolveHelper(input, 10000000000000);
}
