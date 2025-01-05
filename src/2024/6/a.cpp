#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "solution.hpp"

namespace day6a {

const std::array<std::pair<int, int>, 4> dirs = {
    std::pair{-1, 0},
    std::pair{0, 1},
    std::pair{1, 0},
    std::pair{0, -1},
};

struct Board {
  Board(const std::vector<std::string> &lines) {
    size_y = lines.size();
    size_x = lines[0].size();

    map.resize(size_y * size_x);
    visits.resize(size_y * size_x);

    for (size_t i = 0; i < lines.size(); ++i) {
      std::copy(lines[i].data(), lines[i].data() + size_x, map.data() + i * size_x);
    }
  }

  char at(const int y, const int x) const {
    return map[y * size_x + x];
  }

  void set(const int y, const int x, const char c) {
    map[y * size_x + x] = c;
  }

  void visit(const int y, const int x) {
    visits[y * size_x + x] = true;
  }

  bool is_visited(const int y, const int x) const {
    return visits[y * size_x + x];
  }

  std::vector<char> map;
  std::vector<bool> visits;

  int size_y;
  int size_x;
};

std::pair<int, int> FindStartPoint(const Board &board) {
  for (int y = 0; y < board.size_y; ++y) {
    for (int x = 0; x < board.size_x; ++x) {
      if (board.at(y, x) == '^') {
        return {y, x};
      }
    }
  }
  return {0, 0};
}

}  // namespace day6a

template <>
std::string Solve<2024, 6, 'A'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; input >> line;) {
    lines.push_back(line);
  }

  day6a::Board board(lines);

  auto [y, x] = FindStartPoint(board);

  int dir = 0;

  while (y > 0 && y < board.size_y - 1 && x > 0 && x < board.size_x - 1) {
    board.visit(y, x);

    const int new_y = y + day6a::dirs[dir].first;
    const int new_x = x + day6a::dirs[dir].second;

    if (board.at(new_y, new_x) == '#') {
      dir = (dir + 1) % 4;
    } else {
      y = new_y;
      x = new_x;
    }
  }

  int points = 1;

  for (const bool x : board.visits) {
    points += x;
  }

  return std::to_string(points);
}
