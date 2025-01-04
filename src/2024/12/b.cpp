#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "solution.hpp"
#include "utility.hpp"

namespace day12b {

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

  void reset_sides() {
    sides.clear();
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

  int size_y;
  int size_x;

  std::vector<char> map;
  std::vector<bool> visits;

  std::vector<std::array<int, 3>> sides;
};

void DFS(Map &map, const int y, const int x, int &area) {
  map.visit(y, x);
  ++area;

  const char region = map.at(y, x);

#pragma unroll
  for (int i = 0; i < dirs.size(); ++i) {
    const int new_y = y + dirs[i].first;
    const int new_x = x + dirs[i].second;

    if (!map.visited(new_y, new_x) && map.at(new_y, new_x) == region &&
        map.is_inside(new_y, new_x)) {
      DFS(map, new_y, new_x, area);
    }

    if (((map.at(new_y, new_x) != region) || !map.is_inside(new_y, new_x)) && ((i & 1) == 0)) {
      map.sides.push_back({i, new_y, new_x});
    }
  }
}

int SearchSides(Map &map) {
  int sides = 0;

  {  // Search horizontal sides
    std::sort(map.sides.begin(), map.sides.end(),
              [&](const std::array<int, 3> &a, const std::array<int, 3> &b) {
                return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]) ||
                       (a[0] == b[0] && a[1] == b[1] && a[2] < b[2]);
              });

    for (int i = 0; i < map.sides.size();) {
      ++sides;

      while (++i < map.sides.size() && (map.sides[i - 1][0] == map.sides[i][0]) &&
             (map.sides[i - 1][1] == map.sides[i][1]) &&
             ((map.sides[i - 1][2] + 1) == map.sides[i][2]))
        ;
    }
  }

  return sides * 2;
}

}  // namespace day12b

template <>
std::string Solve<2024, 12, 'B'>(std::stringstream input) {
  uint64_t points = 0;

  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  my::Timer timer;

  day12b::Map map(lines);

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (!map.visited(y, x)) {
        int area = 0;

        map.reset_sides();
        day12b::DFS(map, y, x, area);

        const int sides = day12b::SearchSides(map);

        points += area * sides;
      }
    }
  }

  return std::to_string(points);
}
