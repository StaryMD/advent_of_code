#include <algorithm>
#include <array>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
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

  void Print() const {
    for (int y = 0; y < size_y; ++y) {
      for (int x = 0; x < size_x; ++x) {
        std::cout << at(y, x);
      }
      std::cout << '\n';
    }
  }

  void PrintVisits() const {
    for (int y = 0; y < size_y; ++y) {
      for (int x = 0; x < size_x; ++x) {
        if (visited(y, x) == INT_MAX) {
          std::cout << std::left << std::setw(5) << at(y, x);
        } else {
          std::cout << std::left << std::setw(5) << visited(y, x);
        }
      }
      std::cout << '\n';
    }
  }

  int size_y;
  int size_x;

  std::vector<char> map;
  std::vector<int> visits;

  int start_y, start_x;
  int end_y, end_x;
};

void DFS(Map &map, const int y, const int x, int dist) {
  map.visit(y, x, dist);
  ++dist;

#pragma unroll
  for (int i = 0; i < dirs.size(); ++i) {
    const int new_y = y + dirs[i].first;
    const int new_x = x + dirs[i].second;

    if ((dist < map.visited(new_y, new_x)) && map.at(new_y, new_x) != '#') {
      DFS(map, new_y, new_x, dist);
    }
  }
}

int Distance(Map map, const int y1, const int x1, const int y2, const int x2) {
  map.reset_visits();

  DFS(map, y1, x1, 0);

  return map.visited(y2, x2);
}

std::pair<int, int> FindCell(const Map &map, const char c) {
  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.at(y, x) == c) {
        return {y, x};
      }
    }
  }
  return {0, 0};
}

int main() {
  std::ifstream fin("data/20.txt");

  my::Timer timer;

  std::vector<std::string> lines;

  for (std::string line; std::getline(fin, line);) {
    lines.push_back(line);
  }

  Map map(lines);
  Map back_map(map);

  const auto [start_y, start_x] = FindCell(map, 'S');
  const auto [end_y, end_x] = FindCell(map, 'E');

  map.at(start_y, start_x) = '.';
  map.at(end_y, end_x) = '.';

  DFS(map, start_y, start_x, 0);
  DFS(back_map, end_y, end_x, 0);

  constexpr int threshold = 100;
  constexpr int cheat_max_dist = 20;

  const int original_dist = map.visited(end_y, end_x);
  const int max_dist = original_dist - threshold;

  uint64_t points = 0;

  for (int cheat_start_y = 0; cheat_start_y < map.size_y; ++cheat_start_y) {
    for (int cheat_start_x = 0; cheat_start_x < map.size_x; ++cheat_start_x) {
      if (map.at(cheat_start_y, cheat_start_x) == '.') {
        for (int cheat_end_y = 0; cheat_end_y < map.size_y; ++cheat_end_y) {
          for (int cheat_end_x = 0; cheat_end_x < map.size_x; ++cheat_end_x) {
            if (map.at(cheat_end_y, cheat_end_x) == '.') {
              const int cheat_dist =
                  std::abs(cheat_start_x - cheat_end_x) + std::abs(cheat_start_y - cheat_end_y);

              if (cheat_dist <= cheat_max_dist) {
                const int total_dist = map.visited(cheat_start_y, cheat_start_x) + cheat_dist +
                                       back_map.visited(cheat_end_y, cheat_end_x);

                if (total_dist <= max_dist) {
                  points++;
                }
              }
            }
          }
        }
      }
    }
  }

  const double elapsed_time = timer.ElapsedTime();

  std::cout << points << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e3 << " ms\n";
}
