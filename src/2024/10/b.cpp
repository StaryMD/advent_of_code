#include <array>
#include <cstdio>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day10b_2024 {

const std::array<std::pair<int, int>, 4> dirs = {
    std::pair{-1, 0},
    std::pair{0, 1},
    std::pair{1, 0},
    std::pair{0, -1},
};

struct Map {
  Map(const std::vector<std::string> &lines) {
    size_y = lines.size();
    size_x = lines[0].size();

    map.resize(size_y * size_x);

    for (size_t i = 0; i < lines.size(); ++i) {
      std::copy(lines[i].data(), lines[i].data() + size_x, map.data() + i * size_x);
    }
  }

  bool is_inside(const int y, const int x) const {
    return y >= 0 && y < size_y && x >= 0 && x < size_x;
  }

  char at(const int y, const int x) const {
    return map[y * size_x + x];
  }

  int size_y;
  int size_x;

  std::vector<char> map;
};

}  // namespace day10b_2024

template <>
std::string Solve<2024, 10, 'B'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  day10b_2024::Map map(lines);

  int points = 0;

  struct State {
    int y, x;
  };

  std::vector<State> todo;
  std::vector<State> backlog;

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.at(y, x) == '9') {
        todo.emplace_back(y, x);
      }
    }
  }

  while (not todo.empty()) {
    while (not todo.empty()) {
      const auto [y, x] = todo.back();
      todo.pop_back();

      if (map.at(y, x) == '0') {
        ++points;
        continue;
      }

      for (const auto [dy, dx] : day10b_2024::dirs) {
        const int new_y = y + dy;
        const int new_x = x + dx;

        if (map.is_inside(new_y, new_x) && (map.at(new_y, new_x) == map.at(y, x) - 1)) {
          backlog.emplace_back(new_y, new_x);
        }
      }
    }
    std::swap(todo, backlog);
  }

  return std::to_string(points);
}
