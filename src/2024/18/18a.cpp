#include <climits>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
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
  Map(const int y, const int x) {
    size_y = y;
    size_x = x;

    map.resize(size_y * size_x);
    visits.resize(size_y * size_x);
    colors.resize(size_y * size_x);

    std::fill(map.begin(), map.end(), '.');
    std::fill(visits.begin(), visits.end(), INT_MAX);
    std::fill(colors.begin(), colors.end(), 0);
  }

  Map(const std::vector<std::string> &lines) {
    size_y = lines.size();
    size_x = lines[0].size();

    map.resize(size_y * size_x);
    visits.resize(size_y * size_x);
    colors.resize(size_y * size_x);

    for (size_t i = 0; i < lines.size(); ++i) {
      std::copy(lines[i].data(), lines[i].data() + size_x, map.data() + i * size_x);
    }

    std::fill(visits.begin(), visits.end(), INT_MAX);
    std::fill(colors.begin(), colors.end(), 0);
  }

  void reset_visits() {
    std::fill(visits.begin(), visits.end(), INT_MAX);
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

  int visited(const int y, const int x) const {
    return visits[y * size_x + x];
  }

  void visit(const int y, const int x, int score) {
    visits[y * size_x + x] = score;
  }

  int get_color(const int y, const int x) const {
    return colors[y * size_x + x];
  }

  void color(const int y, const int x, const int l) {
    colors[y * size_x + x] = l;
  }

  void unvisit(const int y, const int x) {
    visits[y * size_x + x] = INT_MAX;
  }

  int size_y;
  int size_x;

  std::vector<char> map;
  std::vector<int> visits;
  std::vector<int> colors;
};

void DFS(Map &map, const int y, const int x, int dist) {
  map.visit(y, x, dist);
  ++dist;

#pragma unroll
  for (int i = 0; i < dirs.size(); ++i) {
    const int new_y = y + dirs[i].first;
    const int new_x = x + dirs[i].second;

    if ((dist < map.visited(new_y, new_x)) && map.at(new_y, new_x) != '#' &&
        map.is_inside(new_y, new_x)) {
      DFS(map, new_y, new_x, dist);
    }
  }
}

int main() {
  std::ifstream fin("data/18.txt");

  uint64_t points = 0;

  my::Timer timer;

  std::vector<std::string> lines;

  for (std::string line; std::getline(fin, line);) {
    lines.push_back(line);
  }

  Map map(71, 71);

  for (int i = 0; i < 1024; ++i) {
    std::stringstream ss;
    ss << lines[i];
    int x, y;
    char t;
    ss >> x >> t >> y;

    map.at(y, x) = '#';
  }

  DFS(map, 0, 0, 0);

  const double elapsed_time = timer.ElapsedTime();

  std::cout << map.visited(map.size_y - 1, map.size_x - 1) << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e3 << " ms\n";
}
