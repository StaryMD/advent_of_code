#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "solution.hpp"
#include "utility.hpp"

namespace day15a {

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

  char &at(const int y, const int x) {
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

  void Print() const {
    for (int y = 0; y < size_y; ++y) {
      for (int x = 0; x < size_x; ++x) {
        std::cout << at(y, x);
      }
      std::cout << '\n';
    }
  }

  int size_y;
  int size_x;

  std::vector<char> map;
  std::vector<bool> visits;
};

std::pair<int, int> FindStartPoint(const Map &map) {
  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.at(y, x) == '@') {
        return {y, x};
      }
    }
  }
  return {0, 0};
}

bool MoveVertical(Map &map, const int y, const int x, const int dir) {
  const int new_y = y + dirs[dir].first;
  const int new_x = x + dirs[dir].second;

  switch (map.at(new_y, new_x)) {
    case '.': {
      std::swap(map.at(y, x), map.at(new_y, new_x));
      return true;
    }
    case 'O': {
      if (MoveVertical(map, new_y, new_x, dir)) {
        std::swap(map.at(y, x), map.at(new_y, new_x));
        return true;
      }
    }
    case '#': {
      return false;
    }
  }
  return false;
}

}  // namespace day15a

template <>
std::string Solve<2024, 15, 'A'>(std::stringstream input) {
  std::vector<std::string> lines;
  std::string moves;

  for (std::string line; std::getline(input, line);) {
    if (line.empty()) {
      break;
    }

    lines.push_back(line);
  }

  for (std::string line; std::getline(input, line);) {
    moves += line;
  }

  day15a::Map map(lines);

  auto [y, x] = day15a::FindStartPoint(map);

  for (const char move : moves) {
    switch (move) {
      case '^': {
        if (day15a::MoveVertical(map, y, x, 0)) {
          --y;
        }
        break;
      }
      case '>': {
        if (day15a::MoveVertical(map, y, x, 1)) {
          ++x;
        }
        break;
      }
      case 'v': {
        if (day15a::MoveVertical(map, y, x, 2)) {
          ++y;
        }
        break;
      }
      case '<': {
        if (day15a::MoveVertical(map, y, x, 3)) {
          --x;
        }
        break;
      }
    }
  }

  uint64_t points = 0;

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.at(y, x) == 'O') {
        points += 100 * y + x;
      }
    }
  }

  return std::to_string(points);
}
