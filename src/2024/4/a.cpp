#include <array>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 4, 'A'>(std::stringstream input_stream) {
  constexpr std::array<std::pair<int, int>, 8> dirs = {
      std::make_pair(0, 1),  std::make_pair(1, 1),   std::make_pair(1, 0),  std::make_pair(1, -1),
      std::make_pair(0, -1), std::make_pair(-1, -1), std::make_pair(-1, 0), std::make_pair(-1, 1),
  };

  union Stuff {
    char c[4];
    int a;
  };

  constexpr Stuff xmas = {
      .c = {'X', 'M', 'A', 'S'},
  };

  const std::string &input = input_stream.str();

  const int size_x = input.find('\n');
  const int size_y = input.size() / size_x;

  int points = 0;

  for (int y = 0; y < size_y; ++y) {
    for (int x = 0; x < size_x; ++x) {
      for (const auto [dy, dx] : dirs) {
        if (((0 <= y + 3 * dy) && (y + 3 * dy < size_y)) &&
            ((0 <= x + 3 * dx) && (x + 3 * dx < size_x))) {
          const Stuff stuff = {
              .c =
                  {
                      input[(y + 0 * dy) * (size_x + 1) + x + 0 * dx],
                      input[(y + 1 * dy) * (size_x + 1) + x + 1 * dx],
                      input[(y + 2 * dy) * (size_x + 1) + x + 2 * dx],
                      input[(y + 3 * dy) * (size_x + 1) + x + 3 * dx],
                  },
          };

          points += stuff.a == xmas.a;
        }
      }
    }
  }

  return std::to_string(points);
}
