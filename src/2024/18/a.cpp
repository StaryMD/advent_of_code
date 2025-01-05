#include <array>
#include <climits>
#include <cstdio>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day18a {

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

    std::fill(map.begin(), map.end(), '.');
    std::fill(visits.begin(), visits.end(), INT_MAX);
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

  void unvisit(const int y, const int x) {
    visits[y * size_x + x] = INT_MAX;
  }

  int size_y;
  int size_x;

  std::vector<char> map;
  std::vector<int> visits;
};

void DFS(Map &map, const int goal_y, const int goal_x, const int y, const int x, int dist) {
  struct State {
    int y, x, dist;
  };

  std::deque<State> states;
  states.emplace_back(y, x, dist);
  map.visit(y, x, 0);

  int counter = 0;

  while (not states.empty()) {
    const auto [y, x, dist] = states.front();
    states.pop_front();

    const int new_dist = dist + 1;

    for (int i = 0; i < dirs.size(); ++i) {
      const int new_y = y + dirs[i].first;
      const int new_x = x + dirs[i].second;

      if ((new_dist < map.visited(new_y, new_x)) && map.at(new_y, new_x) != '#' &&
          map.is_inside(new_y, new_x)) {
        states.emplace_back(new_y, new_x, new_dist);
        map.visit(new_y, new_x, new_dist);
      }
    }
  }
}

}  // namespace day18a

template <>
std::string Solve<2024, 18, 'A'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  day18a::Map map(71, 71);

  for (int i = 0; i < 1024; ++i) {
    std::stringstream ss;
    ss << lines[i];
    int x, y;
    char t;
    ss >> x >> t >> y;

    map.at(y, x) = '#';
  }

  DFS(map, map.size_y - 1, map.size_x - 1, 0, 0, 0);

  return std::to_string(map.visited(map.size_y - 1, map.size_x - 1));
}
