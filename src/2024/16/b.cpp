#include <algorithm>
#include <array>
#include <climits>
#include <cstdio>
#include <string>
#include <vector>

#include "common.hpp"
#include "solution.hpp"

namespace day16b {

struct ColoredMap : day16::Map {
  ColoredMap(const std::vector<std::string> &lines) : Map(lines) {
    colors.resize(size_y * size_x);

    std::fill(colors.begin(), colors.end(), 0);
  }

  int get_color(const int y, const int x, const int l) const {
    return colors[y * size_x + x] & (1 << l);
  }

  void color(const int y, const int x, const int l) {
    colors[y * size_x + x] |= 1 << l;
  }

  std::vector<int> colors;
};

bool MarkTrail(ColoredMap &map, const int y, const int x, const int color, const int dir = 1,
               const int score = 0) {
  if (map.at(y, x) == 'E') {
    map.color(y, x, color);

    return true;
  }

  bool is_good = false;

  for (int new_dir = 0; new_dir < 4; ++new_dir) {
    if (is_good || new_dir == (dir + 2) % 4) {
      continue;
    }

    const int new_y = y + day16::dirs[new_dir].first;
    const int new_x = x + day16::dirs[new_dir].second;
    const int new_score = score + ((new_dir == dir) ? 1 : 1001);

    if (new_score == map.visited(new_y, new_x)) {
      is_good |= MarkTrail(map, new_y, new_x, color, new_dir, new_score);
    }
  }

  if (is_good) {
    map.color(y, x, color);
  }

  return is_good;
}

}  // namespace day16b

template <>
std::string Solve<2024, 16, 'B'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  day16b::ColoredMap map(lines);

  const auto [start_y, start_x] = FindCell(map, 'S');
  const auto [end_y, end_x] = FindCell(map, 'E');

  day16::GetTrailScore(map, start_y, start_x);

  const int part1_score = map.visited(end_y, end_x);

  MarkTrail(map, start_y, start_x, 0);

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.get_color(y, x, 0)) {
        int valid_neighs_count = 0;

        for (int dir = 0; dir < 4; ++dir) {
          const int new_y = y + day16::dirs[dir].first;
          const int new_x = x + day16::dirs[dir].second;

          if (map.at(new_y, new_x) != '#') {
            ++valid_neighs_count;
          }
        }

        if (valid_neighs_count > 2) {
          for (int dir = 0; dir < 4; ++dir) {
            const int new_y = y + day16::dirs[dir].first;
            const int new_x = x + day16::dirs[dir].second;

            if (map.get_color(new_y, new_x, 0) && map.visited(new_y, new_x) > map.visited(y, x)) {
              map.color(new_y, new_x, 1);
            }
          }
        }
      }
    }
  }

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.get_color(y, x, 1)) {
        const char prev_val = map.at(y, x);

        map.at(y, x) = '#';
        map.reset_visits();

        day16::GetTrailScore(map, start_y, start_x);

        const int curr_score = map.visited(end_y, end_x);

        if (curr_score == part1_score) {
          MarkTrail(map, start_y, start_x, 2);
        }

        map.at(y, x) = prev_val;
      }
    }
  }

  int points = 0;

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      points += map.get_color(y, x, 2) != 0;
    }
  }

  return std::to_string(points);
}
