#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "solution.hpp"
#include "utility.hpp"

namespace day12a {

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
    visits.resize(size_y * size_x);

    for (size_t i = 0; i < lines.size(); ++i) {
      std::copy(lines[i].data(), lines[i].data() + size_x, map.data() + i * size_x);
    }

    std::fill(visits.begin(), visits.end(), false);
  }

  void reset_visits() {
    std::fill(visits.begin(), visits.end(), false);
  }

  bool can_adv(const int y, const int x, const int new_y, const int new_x) const {
    return is_inside(new_y, new_x) && (at(new_y, new_x) == at(y, x) + 1);
  }

  bool is_inside(const int y, const int x) const {
    return y >= 0 && y < size_y && x >= 0 && x < size_x;
  }

  char at(const int y, const int x) const {
    return map[y * size_x + x];
  }

  bool visited(const int y, const int x) const {
    return visits[y * size_x + x];
  }

  void visit(const int y, const int x) {
    visits[y * size_x + x] = true;
  }

  void unvisit(const int y, const int x) {
    visits[y * size_x + x] = false;
  }

  int size_y;
  int size_x;

  std::vector<char> map;
  std::vector<bool> visits;
};

void DFS(Map &map, const int y, const int x, int &area, int &perimeter) {
  map.visit(y, x);
  area += 1;

  const char region = map.at(y, x);

  for (const auto [dy, dx] : dirs) {
    const int new_y = y + dy;
    const int new_x = x + dx;

    if (map.at(new_y, new_x) == region && map.is_inside(new_y, new_x)) {
      if (not map.visited(new_y, new_x)) {
        DFS(map, new_y, new_x, area, perimeter);
      }
    } else {
      perimeter += 1;
    }
  }
}

}  // namespace day12a

template <>
std::string Solve<2024, 12, 'A'>(std::stringstream input) {
  uint64_t points = 0;

  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  my::Timer timer;

  day12a::Map map(lines);

  struct State {
    int y, x;
  };

  std::vector<State> todo;

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (not map.visited(y, x)) {
        int area = 0;
        int perimeter = 0;

        todo.emplace_back(y, x);

        while (not todo.empty()) {
          const auto [y, x] = todo.back();
          todo.pop_back();

          if (map.visited(y, x)) {
            continue;
          }

          map.visit(y, x);
          ++area;

          const char region = map.at(y, x);

          for (const auto [dy, dx] : day12a::dirs) {
            const int new_y = y + dy;
            const int new_x = x + dx;

            if (map.at(new_y, new_x) == region && map.is_inside(new_y, new_x)) {
              todo.emplace_back(new_y, new_x);
            } else {
              ++perimeter;
            }
          }
        }

        points += area * perimeter;
      }
    }
  }

  return std::to_string(points);
}
