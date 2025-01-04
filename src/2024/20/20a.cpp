#include <climits>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "utility.hpp"

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
        if (at(y, x) == '#') {
          std::cout << std::setw(4) << '#' << ' ';
        } else {
          if (visited(y, x) == INT_MAX) {
            std::cout << std::setw(4) << "  ERR";
          } else {
            std::cout << std::setw(4) << visited(y, x) << ' ';
          }
        }
      }
      std::cout << '\n';
    }
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

  if (map.at(y, x) == 'c') {
    for (int i = 0; i < dirs.size(); ++i) {
      const int new_y = y + dirs[i].first;
      const int new_x = x + dirs[i].second;

      if (map.at(new_y, new_x) == '2') {
        map.at(new_y, new_x) = '.';
        DFS(map, new_y, new_x, dist);
        map.at(new_y, new_x) = '2';
      }
    }
    return;
  }

#pragma unroll
  for (int i = 0; i < dirs.size(); ++i) {
    const int new_y = y + dirs[i].first;
    const int new_x = x + dirs[i].second;

    if (map.at(y, x) == '.') {
      if (map.at(new_y, new_x) == '1') {
        map.at(new_y, new_x) = 'c';
        DFS(map, new_y, new_x, dist);
        map.at(new_y, new_x) = '1';
      } else if (map.at(new_y, new_x) == '.' && (dist < map.visited(new_y, new_x)) &&
                 map.at(new_y, new_x) != '#' && map.is_inside(new_y, new_x)) {
        DFS(map, new_y, new_x, dist);
      }
    }
  }
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

  uint64_t points = 0;

  my::Timer timer;

  std::vector<std::string> lines;

  for (std::string line; std::getline(fin, line);) {
    lines.push_back(line);
  }

  Map map(lines);

  const auto [start_y, start_x] = FindCell(map, 'S');
  const auto [end_y, end_x] = FindCell(map, 'E');

  map.at(start_y, start_x) = '.';
  map.at(end_y, end_x) = '.';

  int original_time = 0;

  {
    Map new_map(map);

    DFS(new_map, start_y, start_x, 0);

    original_time = new_map.visited(end_y, end_x);
  }

  std::cout << "Original time: " << original_time << '\n';
  const int threshold = 100;

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      for (int i = 0; i < dirs.size(); ++i) {
        const int new_y = y + dirs[i].first;
        const int new_x = x + dirs[i].second;

        if (map.is_inside(new_y, new_x) && (map.at(y, x) == '#' && map.at(new_y, new_x) == '.')) {
          Map new_map(map);

          new_map.at(y, x) = '1';
          new_map.at(new_y, new_x) = '2';

          DFS(new_map, start_y, start_x, 0);

          const int time = new_map.visited(end_y, end_x);
          if (time <= original_time - threshold) {
            ++points;

            // new_map.Print();
            // new_map.PrintVisits();
            // std::cout << time << '\n';
            // std::getc(stdin);
          }
        }
      }
    }
  }

  const double elapsed_time = timer.ElapsedTime();

  std::cout << points << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e3 << " ms\n";
}
