#include <algorithm>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
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

  void visit(const int y, const int x, const int score) {
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

void GetTrailScore(Map &map, const int y, const int x, const int dir = 1, const int score = 0) {
  map.visit(y, x, score);

  if (map.at(y, x) == 'E') {
    return;
  }

  for (int i = 0; i < 4; ++i) {
    if (i == (dir + 2) % 4) {
      continue;
    }

    const int new_y = y + dirs[i].first;
    const int new_x = x + dirs[i].second;

    if ((score < map.visited(new_y, new_x) || map.visited(new_y, new_x) == INT_MAX) &&
        map.at(new_y, new_x) != '#') {
      if (i == dir) {
        GetTrailScore(map, new_y, new_x, i, score + 1);
      } else {
        GetTrailScore(map, new_y, new_x, i, score + 1001);
      }
    }
  }
}

int MarkTrail(Map &map, const int y, const int x, const int color, const int dir = 1,
              const int score = 0) {
  if (map.at(y, x) == 'E') {
    if (map.get_color(y, x) == 0 || map.get_color(y, x) != 1) {
      map.color(y, x, color);
    }

    return 1;
  }

  bool is_good = false;

  for (int new_dir = 0; new_dir < 4; ++new_dir) {
    if (new_dir == (dir + 2) % 4) {
      continue;
    }

    const int new_y = y + dirs[new_dir].first;
    const int new_x = x + dirs[new_dir].second;
    const int new_score = score + ((new_dir == dir) ? 1 : 1001);

    if (new_score == map.visited(new_y, new_x)) {
      is_good |= MarkTrail(map, new_y, new_x, color, new_dir, new_score);
    }
  }

  if (is_good && (map.get_color(y, x) == 0 || map.get_color(y, x) != 1)) {
    map.color(y, x, color);
  }

  return is_good;
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
  std::ifstream fin("data/16.txt");

  my::Timer timer;

  std::vector<std::string> lines;

  for (std::string line; std::getline(fin, line);) {
    lines.push_back(line);
  }

  Map map(lines);

  const auto [start_y, start_x] = FindCell(map, 'S');
  const auto [end_y, end_x] = FindCell(map, 'E');

  GetTrailScore(map, start_y, start_x);

  const int part1_score = map.visited(end_y, end_x);
  std::cout << "Part 1 score: " << part1_score << '\n';

  MarkTrail(map, start_y, start_x, 1);

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.get_color(y, x) == 1) {
        const char prev_val = map.at(y, x);

        map.at(y, x) = '#';
        map.reset_visits();

        GetTrailScore(map, start_y, start_x);

        const int curr_score = map.visited(end_y, end_x);
        std::cout << std::format("obs at {} {} got {}\n", y, x, curr_score);

        if (curr_score == part1_score) {
          MarkTrail(map, start_y, start_x, 2);
        }

        map.at(y, x) = prev_val;
      }
    }
  }

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.get_color(y, x) != 0) {
        std::cout << char('A' + map.get_color(y, x) - 1);
      } else {
        std::cout << map.at(y, x);
      }
    }
    std::cout << '\n';
  }

  int points = 0;

  for (const int color : map.colors) {
    points += (color != 0);
  }

  const double elapsed_time = timer.ElapsedTime();

  std::cout << points << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e3 << " ms\n";
}
