#include <algorithm>
#include <array>
#include <climits>
#include <cstdio>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day23b {

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

  // void Print() const {
  //   for (int y = 0; y < size_y; ++y) {
  //     for (int x = 0; x < size_x; ++x) {
  //       std::cout << at(y, x);
  //     }
  //     std::cout << '\n';
  //   }
  // }

  // void PrintVisits() const {
  //   for (int y = 0; y < size_y; ++y) {
  //     for (int x = 0; x < size_x; ++x) {
  //       if (visited(y, x) == INT_MAX) {
  //         std::cout << std::left << std::setw(5) << at(y, x);
  //       } else {
  //         std::cout << std::left << std::setw(5) << visited(y, x);
  //       }
  //     }
  //     std::cout << '\n';
  //   }
  // }

  int size_y;
  int size_x;

  std::vector<char> map;
  std::vector<int> visits;
};

void DFS(Map &map, const int y, const int x, int dist) {
  map.visit(y, x, dist);
  ++dist;

#pragma unroll
  for (int i = 0; i < 4; ++i) {
    const int new_y = y + dirs[i].first;
    const int new_x = x + dirs[i].second;

    if ((dist < map.visited(new_y, new_x)) && map.at(new_y, new_x) != '#') {
      DFS(map, new_y, new_x, dist);
    }
  }
}

}  // namespace day23b

template <>
std::string Solve<2024, 20, 'B'>(std::stringstream input) {
  constexpr int threshold = 100;
  constexpr int cheat_max_dist = 20;

  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  day23b::Map map(lines);
  day23b::Map back_map(map);

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

  DFS(map, start_y, start_x, 0);
  DFS(back_map, end_y, end_x, 0);

  int points = 0;

  for (int path_y = end_y, path_x = end_x; path_y != start_y || path_x != start_x;) {
#pragma unroll
    for (int i = 0; i < 4; ++i) {
      const int new_y = path_y + day23b::dirs[i].first;
      const int new_x = path_x + day23b::dirs[i].second;

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
        const int left = std::max(1, path_x - cheat_max_dist);
        const int right = std::min(map.size_x - 1, path_x + cheat_max_dist) + 1;

        for (int cheat_end_x = left; cheat_end_x != right; ++cheat_end_x) {
          if (map.at(cheat_end_y, cheat_end_x) == '.') {
            const int cheat_dist = std::abs(path_x - cheat_end_x) + std::abs(path_y - cheat_end_y);

            if (cheat_dist <= cheat_max_dist) {
              const int total_dist = map.visited(path_y, path_x) + cheat_dist +
                                     back_map.visited(cheat_end_y, cheat_end_x);

              if (total_dist <= map.visited(end_y, end_x) - threshold) {
                points++;
              }
            }
          }
        }
      }
    }
  }

  return std::to_string(points);
}
