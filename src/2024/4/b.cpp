#include <array>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 4, 'B'>(std::stringstream input_stream) {
  const std::string &input = input_stream.str();

  const int size_x = input.find('\n');
  const int size_y = input.size() / size_x;

  int points = 0;

  for (int y = 1; y < size_y - 1; ++y) {
    for (int x = 1; x < size_x - 1; ++x) {
      if (input[y * (size_x + 1) + x] == 'A') {
        const char str[] = {
            input[(y - 1) * (size_x + 1) + x - 1],
            input[(y - 1) * (size_x + 1) + x + 1],
            input[(y + 1) * (size_x + 1) + x + 1],
            input[(y + 1) * (size_x + 1) + x - 1],
        };

        if (str[0] == 'M') {
          if (str[1] == 'M') {
            points += str[2] == 'S' && str[3] == 'S';
          } else if (str[1] == 'S') {
            points += str[2] == 'S' && str[3] == 'M';
          }
        } else if (str[0] == 'S') {
          if (str[1] == 'M') {
            points += str[2] == 'M' && str[3] == 'S';
          } else if (str[1] == 'S') {
            points += str[2] == 'M' && str[3] == 'M';
          }
        }
      }
    }
  }

  return std::to_string(points);
}
