#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "utils.hpp"

struct Board {
  Board(const std::vector<std::string> &lines) {
    map.resize(lines.size() * lines[0].size());

    map_y = lines.size();
    map_x = lines[0].size();

    for (int i = 0; i < lines.size(); ++i) {
      std::copy(lines[i].data(), lines[i].data() + map_x, map.data() + i * map_x);
    }
  }

  char at(const int y, const int x) const {
    return map[y * map_x + x];
  }

  void set(const int y, const int x, const char c) {
    map[y * map_x + x] = c;
  }

  std::vector<char> map;
  int map_y;
  int map_x;
};

const std::vector<std::pair<int, int>> dirs = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

bool CheckIfInLoop(const Board &board, int y, int x) {
  int dir = 0;

  std::vector<bool> visit(board.map_x * board.map_y * 4);

  while (y > 0 && y < board.map_y - 1 && x > 0 && x < board.map_x - 1) {
    const int new_y = y + dirs[dir].first;
    const int new_x = x + dirs[dir].second;

    if (board.at(new_y, new_x) == '#') {
      if (visit[(y * board.map_x + x) * 4 + dir]) {
        return true;
      }

      visit[(y * board.map_x + x) * 4 + dir] = true;
      dir = (dir + 1) % 4;
    } else {
      y = new_y;
      x = new_x;
    }
  }

  return false;
}

int main() {
  std::ifstream fin("data/6.txt");

  std::vector<std::string> lines;

  for (std::string line; fin >> line;) {
    lines.push_back(line);
  }

  my::Timer timer;

  Board board(lines);

  int start_y = 0;
  int start_x = 0;

  for (int y = 0; y < board.map_y; ++y) {
    for (int x = 0; x < board.map_x; ++x) {
      if (board.at(y, x) == '^') {
        start_y = y;
        start_x = x;
        goto L_STOP;
      }
    }
  }
L_STOP:

  int y = start_y;
  int x = start_x;

  int points = 0;
  int dir = 0;

  while (y > 0 && y < board.map_y - 1 && x > 0 && x < board.map_x - 1) {
    const int new_y = y + dirs[dir].first;
    const int new_x = x + dirs[dir].second;

    if (board.at(new_y, new_x) == '#') {
      dir = (dir + 1) % 4;
    } else {
      y = new_y;
      x = new_x;

      if (board.at(y, x) != ',') {
        board.set(y, x, '#');

        points += CheckIfInLoop(board, start_y, start_x);

        board.set(y, x, ',');
      }
    }
  }

  const double elapsed_time = timer.ElapsedTime();

  std::cout << points << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e3 << " ms\n";

  return 0;
}

