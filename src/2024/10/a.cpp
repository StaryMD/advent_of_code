#include <cstdio>
#include <string>
#include <vector>

#include "solution.hpp"
#include "utility.hpp"

namespace day10a {

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

void CountTrailheadScore(Map &map, const int y, const int x, int* score) {
  if (map.at(y, x) == '9') {
    if (!map.visited(y, x)) {
      map.visit(y, x);
      ++(*score);
    }

    return;
  }

  for (const auto [dy, dx] : dirs) {
    const int new_y = y + dy;
    const int new_x = x + dx;

    if (map.can_adv(y, x, new_y, new_x)) {
      CountTrailheadScore(map, new_y, new_x, score);
    }
  }
}

}  // namespace day10a

template <>
std::string Solve<2024, 10, 'A'>(std::stringstream input) {
  int points = 0;

  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  my::Timer timer;

  day10a::Map map(lines);

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (lines[y][x] == '0') {
        map.reset_visits();
        day10a::CountTrailheadScore(map, y, x, &points);
      }
    }
  }

  return std::to_string(points);
}
