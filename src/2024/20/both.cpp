#include <algorithm>
#include <array>
#include <climits>
#include <cstdio>
#include <deque>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day20 {

const std::array<std::pair<int, int>, 4> dirs = {
    std::pair{-1, 0},
    std::pair{0, 1},
    std::pair{1, 0},
    std::pair{0, -1},
};

struct Map {
  Map(const Map &) = default;
  Map(Map &&) = default;
  Map &operator=(const Map &) = default;
  Map &operator=(Map &&) = default;

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

void DFS(Map &map, const int y, const int x) {
  struct State {
    int y, x, dist;
  };

  std::deque<State> states;
  states.emplace_back(y, x, 0);

  while (not states.empty()) {
    const auto [y, x, dist] = states.front();
    states.pop_front();

    map.visit(y, x, dist);

    const int new_dist = dist + 1;

#pragma unroll
    for (int i = 0; i < 4; ++i) {
      const int new_y = y + dirs[i].first;
      const int new_x = x + dirs[i].second;

      if (new_dist < map.visited(new_y, new_x) && map.at(new_y, new_x) != '#') {
        states.emplace_back(new_y, new_x, new_dist);
      }
    }
  }
}

std::string SolveHelper(std::stringstream &input, const int cheat_max_dist) {
  constexpr int threshold = 100;

  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  Map map(lines);
  Map back_map(map);

  int start_y = 0;
  int start_x = 0;
  int end_y = 0;
  int end_x = 0;

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.at(y, x) == 'S') {
        start_y = y;
        start_x = x;
      } else if (map.at(y, x) == 'E') {
        end_y = y;
        end_x = x;
      }
    }
  }

  map.at(start_y, start_x) = '.';
  map.at(end_y, end_x) = '.';

  DFS(map, start_y, start_x);
  DFS(back_map, end_y, end_x);

  int points = 0;

  for (int path_y = end_y, path_x = end_x; path_y != start_y || path_x != start_x;) {
#pragma unroll
    for (int i = 0; i < 4; ++i) {
      const int new_y = path_y + dirs[i].first;
      const int new_x = path_x + dirs[i].second;

      if (map.visited(new_y, new_x) < map.visited(path_y, path_x)) {
        path_y = new_y;
        path_x = new_x;
        break;
      }
    }

    if (map.at(path_y, path_x) == '.') {
      const int top = std::max(1, path_y - cheat_max_dist);
      const int bot = std::min(map.size_y - 1, path_y + cheat_max_dist) + 1;

      for (int cheat_end_y = top; cheat_end_y != bot; ++cheat_end_y) {
        const int displacement = cheat_max_dist - std::abs(path_y - cheat_end_y);

        const int left = std::max(1, path_x - displacement);
        const int right = std::min(map.size_x - 1, path_x + displacement) + 1;

        for (int cheat_end_x = left; cheat_end_x != right; ++cheat_end_x) {
          const int cheat_dist = std::abs(path_x - cheat_end_x) + std::abs(path_y - cheat_end_y);
          const int total_dist =
              map.visited(path_y, path_x) + cheat_dist + back_map.visited(cheat_end_y, cheat_end_x);

          if (map.at(cheat_end_y, cheat_end_x) == '.' &&
              total_dist <= map.visited(end_y, end_x) - threshold) {
            points++;
          }
        }
      }
    }
  }

  return std::to_string(points);
}

}  // namespace day20

template <>
std::string Solve<2024, 20, 'A'>(std::stringstream input) {
  return day20::SolveHelper(input, 2);
}

template <>
std::string Solve<2024, 20, 'B'>(std::stringstream input) {
  return day20::SolveHelper(input, 20);
}
