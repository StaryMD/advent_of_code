#include <cstdio>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

const std::vector<std::pair<int, int>> dirs = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

bool CheckIfInLoop(const std::vector<std::string> &lines, int y, int x) {
  bool in_loop = false;
  int dir = 0;

  std::set<std::tuple<int, int, int>> set;

  while (!in_loop && y > 0 && y < lines.size() - 1 && x > 0 && x < lines[0].size() - 1) {
    const int new_y = y + dirs[dir].first;
    const int new_x = x + dirs[dir].second;

    if (lines[new_y][new_x] == '#') {
      if (set.find({dir, y, x}) != set.end()) {
        in_loop = true;
      }
      set.insert({dir, y, x});
      dir = (dir + 1) % 4;
    } else {
      y = new_y;
      x = new_x;
    }
  }

  return in_loop;
}

int main() {
  std::ifstream fin("data/6.txt");

  std::vector<std::string> lines;

  for (std::string line; fin >> line;) {
    lines.push_back(line);
  }

  int start_y = 0;
  int start_x = 0;

  for (int y = 0; y < lines.size(); ++y) {
    for (int x = 0; x < lines[y].size(); ++x) {
      if (lines[y][x] == '^') {
        start_y = y;
        start_x = x;
        break;
      }
    }
  }

  int points = 0;

  for (int y = 0; y < lines.size(); ++y) {
    for (int x = 0; x < lines[0].size(); ++x) {
      if (lines[y][x] == '.') {
        lines[y][x] = '#';

        if (CheckIfInLoop(lines, start_y, start_x)) {
          points++;
        }

        lines[y][x] = '.';
      }
    }
  }

  std::cout << points << '\n';

  return 0;
}

