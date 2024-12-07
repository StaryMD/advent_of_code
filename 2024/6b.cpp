#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "utils.hpp"

struct Board {
  Board(const std::vector<std::string> &lines) {
    map.resize(lines.size() * lines[0].size());

    map_y = lines.size();
    map_x = lines[0].size();

    for (size_t i = 0; i < lines.size(); ++i) {
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

bool CheckIfInLoop(const Board &board, int y, int x, int dir) {
  std::vector<bool> visit(board.map_x * board.map_y * 2);

  while (y > 0 && y < board.map_y - 1 && x > 0 && x < board.map_x - 1) {
    const int new_y = y + dirs[dir].first;
    const int new_x = x + dirs[dir].second;

    if (board.at(new_y, new_x) == '#') {
      if (visit[(y * board.map_x + x) * 2 + (dir & 1)]) {
        return true;
      }

      visit[(y * board.map_x + x) * 2 + (dir & 1)] = true;
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

  std::vector<double> times(100);

  for (double &time : times) {
    Board board(lines);

    const my::Timer timer;

    int start_y = 39;
    int start_x = 46;

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
        if (board.at(new_y, new_x) != ',') {
          board.set(new_y, new_x, '#');

          points += CheckIfInLoop(board, y, x, dir);

          board.set(new_y, new_x, ',');
        }
        y = new_y;
        x = new_x;
      }
    }

    if (points != 1705) {
      std::cerr << "cooked : " << points << '\n';
      return EXIT_FAILURE;
    }

    time = timer.ElapsedTime();
  }

  std::cout << std::fixed << std::setprecision(3)
            << std::accumulate(times.begin(), times.end(), 0.0) * 1000 / times.size() << " ms\n";

  return 0;
}

