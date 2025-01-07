#pragma once

#include <array>
#include <climits>
#include <string>
#include <vector>

namespace day16 {

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

  char &at(const int y, const int x) {
    return map[y * size_x + x];
  }

  char at(const int y, const int x) const {
    return map[y * size_x + x];
  }

  int visited(const int y, const int x) const {
    return visits[y * size_x + x];
  }

  void visit(const int y, const int x, const int score) {
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

inline void GetTrailScore(Map &map, const int y, const int x, const int dir = 1,
                          const int score = 0) {
  /*
   * Use a double stack because turns are so very expensive that they will almost always be replaced
   * by a path with less turns. This massibely reduces the number of times a cell will be visited.
   * Idea shamelessly stolen from
   * https://github.com/maneatingape/advent-of-code-rust/blob/db8c7515fb4720b0e570eeee55e8f6f9dc6f08b4/src/year2024/day16.rs
   */
  struct State {
    int y, x, dir, score;
  };

  std::vector<State> first_states;
  std::vector<State> second_states;
  first_states.emplace_back(y, x, dir, score);

  int counter = 0;

  while (not first_states.empty()) {
    while (not first_states.empty()) {
      const auto [y, x, dir, score] = first_states.back();
      first_states.pop_back();
      map.visit(y, x, score);

      for (int i = 0; i < 4; ++i) {
        if (i == (dir + 2) % 4) {
          continue;
        }

        const int new_y = y + dirs[i].first;
        const int new_x = x + dirs[i].second;

        if (score < map.visited(new_y, new_x) && map.at(new_y, new_x) != '#') {
          if (i == dir) {
            first_states.emplace_back(new_y, new_x, i, score + 1);
          } else {
            second_states.emplace_back(new_y, new_x, i, score + 1001);
          }
        }
      }
    }

    std::swap(first_states, second_states);
  }
}

inline std::pair<int, int> FindCell(const Map &map, const char c) {
  for (int y = 0; y < map.size_y; ++y) {
    for (int x = 0; x < map.size_x; ++x) {
      if (map.at(y, x) == c) {
        return {y, x};
      }
    }
  }
  return {0, 0};
}

}  // namespace day16
