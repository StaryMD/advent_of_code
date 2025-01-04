#include <algorithm>
#include <array>
#include <climits>
#include <cstdio>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day16b {

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

  int get_color(const int y, const int x, const int l) const {
    return colors[y * size_x + x] & (1 << l);
  }

  void color(const int y, const int x, const int l) {
    colors[y * size_x + x] |= 1 << l;
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

  for (int i = 0; i < 4; ++i) {
    const int new_dir = (i + dir) % 4;

    if (new_dir == (dir + 2) % 4) {
      continue;
    }

    const int new_y = y + dirs[new_dir].first;
    const int new_x = x + dirs[new_dir].second;

    if ((score < map.visited(new_y, new_x) || map.visited(new_y, new_x) == INT_MAX) &&
        map.at(new_y, new_x) != '#') {
      if (new_dir == dir) {
        GetTrailScore(map, new_y, new_x, new_dir, score + 1);
      } else {
        GetTrailScore(map, new_y, new_x, new_dir, score + 1001);
      }
    }
  }
}

bool MarkTrail(Map &map, const int y, const int x, const int color, const int dir = 1,
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

    const int new_y = y + dirs[new_dir].first;
    const int new_x = x + dirs[new_dir].second;
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

}  // namespace day16b

template <>
std::string Solve<2024, 16, 'B'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  day16b::Map map(lines);

  const auto [start_y, start_x] = FindCell(map, 'S');
  const auto [end_y, end_x] = FindCell(map, 'E');

  GetTrailScore(map, start_y, start_x);

  const int part1_score = map.visited(end_y, end_x);

  MarkTrail(map, start_y, start_x, 0);

  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.get_color(y, x, 0)) {
        int valid_neighs_count = 0;

        for (int dir = 0; dir < 4; ++dir) {
          const int new_y = y + day16b::dirs[dir].first;
          const int new_x = x + day16b::dirs[dir].second;

          if (map.at(new_y, new_x) != '#') {
            ++valid_neighs_count;
          }
        }

        if (valid_neighs_count > 2) {
          for (int dir = 0; dir < 4; ++dir) {
            const int new_y = y + day16b::dirs[dir].first;
            const int new_x = x + day16b::dirs[dir].second;

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

        GetTrailScore(map, start_y, start_x);

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
