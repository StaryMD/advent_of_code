#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "solution.hpp"

const std::array<std::pair<int, int>, 4> dirs = {
    std::pair{-1, 0},
    std::pair{0, 1},
    std::pair{1, 0},
    std::pair{0, -1},
};

struct Board {
  Board(const std::vector<std::string> &lines) {
    map_y = lines.size();
    map_x = lines[0].size();

    map.resize(map_y * map_x);

    for (size_t i = 0; i < lines.size(); ++i) {
      std::copy(lines[i].data(), lines[i].data() + map_x, map.data() + i * map_x);
    }

    map_transposed.resize(map_y * map_x);

    for (int y = 0; y < map_y; ++y) {
      for (int x = 0; x < map_x; ++x) {
        map_transposed[x * map_x + y] = map[y * map_y + x];
      }
    }
  }

  char at(const int y, const int x) const {
    return map[y * map_x + x];
  }

  void set(const int y, const int x, const char c) {
    map[y * map_x + x] = c;
  }

  std::vector<char> map;
  std::vector<char> map_transposed;
  int map_y;
  int map_x;
};

struct StopsMap {
  StopsMap(const Board &board) : board(board) {
    stops_map.resize(board.map_x * board.map_y * 4);

    for (int start_y = 0; start_y < board.map_y; ++start_y) {
      for (int start_x = 0; start_x < board.map_x; ++start_x) {
        if (board.at(start_y, start_x) == '#') {
          AddObstacle(start_y, start_x);
        }
      }
    }
  }

  void AddObstacle(const int obs_y, const int obs_x) {
#define STUFF(forward)                                                                        \
  {                                                                                           \
    const int curr_start_y = obs_y + dirs[(forward)].first;                                   \
    const int curr_start_x = obs_x + dirs[(forward)].second;                                  \
                                                                                              \
    const int back = ((forward) + 2) % 4;                                                     \
    const int left = ((forward) + 3) % 4;                                                     \
    const int redirect_index = (curr_start_y * board.map_x + curr_start_x) * 4 + back;        \
                                                                                              \
    int y = curr_start_y;                                                                     \
    int x = curr_start_x;                                                                     \
                                                                                              \
    while (y >= 0 && y < board.map_y && x >= 0 && x < board.map_x && board.at(y, x) != '#') { \
      y += dirs[left].first;                                                                  \
      x += dirs[left].second;                                                                 \
    }                                                                                         \
                                                                                              \
    if (y >= 0 && y < board.map_y && x >= 0 && x < board.map_x && board.at(y, x) == '#') {    \
      const int prev_y = y - dirs[left].first;                                                \
      const int prev_x = x - dirs[left].second;                                               \
                                                                                              \
      past.push_back({redirect_index, stops_map[redirect_index]});                            \
                                                                                              \
      stops_map[redirect_index] = (prev_y * board.map_x + prev_x) * 4 + left;                 \
    }                                                                                         \
  }
    STUFF(0)
    STUFF(1)
    STUFF(2)
    STUFF(3)

#undef STUFF
  }

  void CorrectPathsAroundObstacle(const int obs_y, const int obs_x) {
#define STUFF(forward)                                                                   \
  {                                                                                      \
    const int curr_start_y = obs_y + dirs[(forward)].first;                              \
    const int curr_start_x = obs_x + dirs[(forward)].second;                             \
                                                                                         \
    const int right = ((forward) + 1) % 4;                                               \
    const int back = ((forward) + 2) % 4;                                                \
    const int redirect_index = (curr_start_y * board.map_x + curr_start_x) * 4 + back;   \
                                                                                         \
    int y = curr_start_y;                                                                \
    int x = curr_start_x;                                                                \
                                                                                         \
    int cand_y = curr_start_y + dirs[right].first;                                       \
    int cand_x = curr_start_x + dirs[right].second;                                      \
                                                                                         \
    while (cand_y >= 0 && cand_y < board.map_y && cand_x >= 0 && cand_x < board.map_x && \
           board.at(y, x) != '#') {                                                      \
      if (board.at(cand_y, cand_x) == '#') {                                             \
        const int stop_index = (y * board.map_x + x) * 4 + right;                        \
                                                                                         \
        past.push_back({stop_index, stops_map[stop_index]});                             \
                                                                                         \
        stops_map[stop_index] = redirect_index;                                          \
      }                                                                                  \
                                                                                         \
      y += dirs[(forward)].first;                                                        \
      x += dirs[(forward)].second;                                                       \
                                                                                         \
      cand_y += dirs[(forward)].first;                                                   \
      cand_x += dirs[(forward)].second;                                                  \
    }                                                                                    \
  }
    STUFF(0)
    STUFF(1)
    STUFF(2)
    STUFF(3)

#undef STUFF
  }

  void UndoFuture() {
    for (const auto [id, val] : past) {
      stops_map[id] = val;
    }
  }

  std::vector<int> stops_map;
  std::vector<std::pair<int, int>> past;
  const Board &board;
};

bool CheckIfInLoop(const Board &board, const StopsMap &stops_map, const int y, const int x,
                   const int dir) {
  std::vector<bool> visit(board.map_x * board.map_y * 4);

  int curr_pos = (y * board.map_x + x) * 4 + dir;

  while (curr_pos != 0) {
    if (visit[curr_pos]) {
      return true;
    }

    visit[curr_pos] = true;
    curr_pos = stops_map.stops_map[curr_pos];
  }

  return false;
}

std::pair<int, int> FindStartPoint(const Board &board) {
  for (int y = 0; y < board.map_y; ++y) {
    for (int x = 0; x < board.map_x; ++x) {
      if (board.at(y, x) == '^') {
        return {y, x};
      }
    }
  }
  return {0, 0};
}

template <>
std::string Solve<2024, 6, 'B'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; input >> line;) {
    lines.push_back(line);
  }

  Board board(lines);
  StopsMap stops_map(board);

  auto [y, x] = FindStartPoint(board);

  int points = 0;
  int dir = 0;

  while (y > 0 && y < board.map_y - 1 && x > 0 && x < board.map_x - 1) {
    const int new_y = y + dirs[dir].first;
    const int new_x = x + dirs[dir].second;

    if (board.at(new_y, new_x) == '#') {
      dir = (dir + 1) % 4;
    } else {
      if (board.at(new_y, new_x) != ',') {
        stops_map.past.clear();

        stops_map.AddObstacle(new_y, new_x);
        stops_map.CorrectPathsAroundObstacle(new_y, new_x);

        points += CheckIfInLoop(board, stops_map, y, x, dir);

        stops_map.UndoFuture();

        board.set(new_y, new_x, ',');
      }
      y = new_y;
      x = new_x;
    }
  }

  return std::to_string(points);
}
