#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"

const std::array<std::pair<int, int>, 4> dirs = {
    std::pair{-1, 0},
    std::pair{0, 1},
    std::pair{1, 0},
    std::pair{0, -1},
};

struct Map {
  Map(const std::vector<std::string> &lines) {
    size_y = lines.size();
    size_x = lines[0].size() * 2;

    map.resize(size_y * size_x);
    visits.resize(size_y * size_x);

    for (size_t y = 0; y < lines.size(); ++y) {
      for (size_t x = 0; x < lines[0].size(); ++x) {
        switch (lines[y][x]) {
          case '#': {
            at(y, x * 2) = '#';
            at(y, x * 2 + 1) = '#';
            break;
          }
          case 'O': {
            at(y, x * 2) = '[';
            at(y, x * 2 + 1) = ']';
            break;
          }
          case '@': {
            at(y, x * 2) = '@';
            at(y, x * 2 + 1) = '.';
            break;
          }
          case '.': {
            at(y, x * 2) = '.';
            at(y, x * 2 + 1) = '.';
            break;
          }
        }
      }
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

bool MoveHorizontal(Map &map, const int y, const int x, const int dir) {
  const int a = dirs[dir].second;

  switch (map.at(y, x + a)) {
    case '.': {
      std::swap(map.at(y, x), map.at(y, x + a));
      return true;
    }
    case '[': {
      if (MoveHorizontal(map, y, x + a * 2, dir)) {
        std::swap(map.at(y, x + a), map.at(y, x + a * 2));
        std::swap(map.at(y, x), map.at(y, x + a));
        return true;
      }
    }
    case ']': {
      if (MoveHorizontal(map, y, x + a * 2, dir)) {
        std::swap(map.at(y, x + a), map.at(y, x + a * 2));
        std::swap(map.at(y, x), map.at(y, x + a));
        return true;
      }
    }
  }
  return false;
}

bool MoveVertical(Map &map, const int y, const int x, const int dir) {
  const int a = dirs[dir].first;
  const int new_y = y + a;

  switch (map.at(new_y, x)) {
    case '.': {
      std::swap(map.at(y, x), map.at(new_y, x));
      return true;
    }
    case '[': {
      if (MoveVertical(map, new_y, x, dir) && MoveVertical(map, new_y, x + 1, dir)) {
        std::swap(map.at(y, x), map.at(new_y, x));
        return true;
      }
      break;
    }
    case ']': {
      if (MoveVertical(map, new_y, x - 1, dir) && MoveVertical(map, new_y, x, dir)) {
        std::swap(map.at(y, x), map.at(new_y, x));
        return true;
      }
      break;
    }
  }
  return false;
}

int main() {
  my::Timer timer;

  std::ifstream fin("data/15.txt");

  std::vector<std::string> lines;
  std::string moves;

  for (std::string line; std::getline(fin, line);) {
    if (line.empty()) {
      break;
    }

    lines.push_back(line);
  }

  for (std::string line; std::getline(fin, line);) {
    moves += line;
  }

  Map map(lines);

  auto [y, x] = FindStartPoint(map);

  for (int i = 0; i < moves.size(); ++i) {
    const char move = moves[i];
    const Map prev_map = map;

    switch (move) {
      case '^': {
        if (MoveVertical(map, y, x, 0)) {
          --y;
        } else {
          map = prev_map;
        }
        break;
      }
      case '>': {
        if (MoveHorizontal(map, y, x, 1)) {
          ++x;
        }
        break;
      }
      case 'v': {
        if (MoveVertical(map, y, x, 2)) {
          ++y;
        } else {
          map = prev_map;
        }
        break;
      }
      case '<': {
        if (MoveHorizontal(map, y, x, 3)) {
          --x;
        }
        break;
      }
    }
  }

  uint64_t points = 0;

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.at(y, x) == '[') {
        points += 100 * y + x;
      }
    }
  }

  const double elapsed_time = timer.ElapsedTime();

  std::cout << points << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e3 << " ms\n";
}
