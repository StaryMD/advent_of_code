#include <array>
#include <climits>
#include <cstdio>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day18b {

struct Point {
  int y, x;
};

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

  Map(const std::vector<std::string> &lines) {
    size_y = lines.size();
    size_x = lines[0].size();

    map.resize(size_y * size_x);
    visits.resize(size_y * size_x);

    for (size_t i = 0; i < lines.size(); ++i) {
      std::copy(lines[i].data(), lines[i].data() + size_x, map.data() + i * size_x);
    }

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

int Dist(Map &map, const int goal_y, const int goal_x, const int y, const int x) {
  struct State {
    int y, x;
  };

  std::vector<State> todo;
  std::vector<State> backlog;

  todo.emplace_back(y, x);
  map.visit(y, x, 0);

  int dist = 0;

  while (not todo.empty()) {
    ++dist;

    while (not todo.empty()) {
      const auto [y, x] = todo.back();
      todo.pop_back();

      for (int i = 0; i < dirs.size(); ++i) {
        const int new_y = y + dirs[i].first;
        const int new_x = x + dirs[i].second;

        if ((dist < map.visited(new_y, new_x)) && map.at(new_y, new_x) != '#' &&
            map.is_inside(new_y, new_x)) {
          backlog.emplace_back(new_y, new_x);
          map.visit(new_y, new_x, dist);
        }
      }
    }

    std::swap(todo, backlog);
  }

  return map.visited(goal_y, goal_x);
}

}  // namespace day18b

template <>
std::string Solve<2024, 18, 'B'>(std::stringstream input) {
  using namespace day18b;

  std::vector<Point> points;

  {
    int x, y;
    char c;
    while (input >> x >> c >> y) {
      points.emplace_back(y, x);
    }
  }

  Map map(71, 71);

  for (int i = 0; i < 1024; ++i) {
    map.at(points[i].y, points[i].x) = '#';
  }

  int left = 1024;
  int right = points.size();

  while (left < right) {
    const int mid = (left + right) / 2;

    Map new_map(map);
    for (int i = 1024; i <= mid; ++i) {
      new_map.at(points[i].y, points[i].x) = '#';
    }

    new_map.reset_visits();
    const int dist_till_end = Dist(new_map, new_map.size_y - 1, new_map.size_x - 1, 0, 0);

    if (dist_till_end == INT_MAX) {
      right = mid;
    } else {
      for (int i = left; i <= mid; ++i) {
        map.at(points[i].y, points[i].x) = '#';
      }
      left = mid + 1;
    }
  }

  return std::to_string(points[right].x) + ',' + std::to_string(points[right].y);
}
