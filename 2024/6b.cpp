#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <numeric>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "utils.hpp"

const std::vector<std::pair<int, int>> dirs = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

struct Board {
  Board(const std::vector<std::string> &lines) {
    map.resize(lines.size() * lines[0].size());

    map_y = lines.size();
    map_x = lines[0].size();

    for (size_t i = 0; i < lines.size(); ++i) {
      std::copy(lines[i].data(), lines[i].data() + map_x, map.data() + i * map_x);
    }
  }

  char at(const int y, const int x) const {
    return map[y * map_x + x];
  }

  void set(const int y, const int x, const char c) {
    map[y * map_x + x] = c;
  }

  friend std::ostream &operator<<(std::ostream &out, const Board &board) {
    for (int y = 0; y < board.map_y; ++y) {
      for (int x = 0; x < board.map_x; ++x) {
        const int index = y * board.map_x + x;
        out << board.map[index];
      }
      out << '\n';
    }

    return out;
  }

  std::vector<char> map;
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

  void AddObstacle(const int start_y, const int start_x) {
    for (int dir0 = 0; dir0 < static_cast<int>(dirs.size()); ++dir0) {
      const int curr_start_y = start_y + dirs[dir0].first;
      const int curr_start_x = start_x + dirs[dir0].second;
      const int dir = (dir0 + 3) % 4;

      int y = curr_start_y;
      int x = curr_start_x;

      while (y >= 0 && y < board.map_y && x >= 0 && x < board.map_x && board.at(y, x) != '#') {
        y += dirs[dir].first;
        x += dirs[dir].second;
      }

      if (y >= 0 && y < board.map_y && x >= 0 && x < board.map_x && board.at(y, x) == '#') {
        const int prev_y = y - dirs[dir].first;
        const int prev_x = x - dirs[dir].second;
        const int funny_id = (curr_start_y * board.map_x + curr_start_x) * 4 + (dir0 + 2) % 4;

        past.push_back({funny_id, stops_map[funny_id]});

        stops_map[(curr_start_y * board.map_x + curr_start_x) * 4 + (dir0 + 2) % 4] =
            (prev_y * board.map_x + prev_x) * 4 + dir;
      }
    }
  }

  void CorrectPathsAroundObstacle(const int obs_y, const int obs_x) {
    for (int dir = 0; dir < static_cast<int>(dirs.size()); ++dir) {
      const int curr_start_y = obs_y + dirs[dir].first;
      const int curr_start_x = obs_x + dirs[dir].second;
      const int towards_obs = (dir + 2) % 4;
      const int redirect_index = (curr_start_y * board.map_x + curr_start_x) * 4 + towards_obs;
      const std::pair<int, int> right_dir = dirs[(dir + 1) % 4];

      int y = curr_start_y;
      int x = curr_start_x;

      int cand_y = curr_start_y + right_dir.first;
      int cand_x = curr_start_x + right_dir.second;

      while (cand_y >= 0 && cand_y < board.map_y && cand_x >= 0 && cand_x < board.map_x &&
             board.at(y, x) != '#') {
        if (board.at(cand_y, cand_x) == '#') {
          const int stop_index = (y * board.map_x + x) * 4 + (dir + 1) % 4;

          past.push_back({stop_index, stops_map[stop_index]});

          stops_map[stop_index] = redirect_index;
        }

        y += dirs[dir].first;
        x += dirs[dir].second;

        cand_y += dirs[dir].first;
        cand_x += dirs[dir].second;
      }
    }
  }

  template <typename functor_t>
  void TestWithObstacle(const int obs_y, const int obs_x, const functor_t &functor) {
    past.clear();

    AddObstacle(obs_y, obs_x);
    CorrectPathsAroundObstacle(obs_y, obs_x);

    functor();

    UndoFuture();
  }

  void UndoFuture() {
    for (const auto [id, val] : past) {
      stops_map[id] = val;
    }
  }

  friend std::ostream &operator<<(std::ostream &out, const StopsMap &stops_map) {
    for (size_t i = 0; i < stops_map.stops_map.size(); ++i) {
      if (stops_map.stops_map[i] != 0) {
        const int from_y = (i / 4) / stops_map.board.map_x;
        const int from_x = (i / 4) % stops_map.board.map_x;
        const int from_dir = i % 4;

        const int to_y = (stops_map.stops_map[i] / 4) / stops_map.board.map_x;
        const int to_x = (stops_map.stops_map[i] / 4) % stops_map.board.map_x;
        const int to_dir = stops_map.stops_map[i] % 4;

        out << std::format("direct ({}, {}, {}) to ({}, {}, {})\n", from_y + 1, from_x + 1,
                           from_dir, to_y + 1, to_x + 1, to_dir);
      }
    }

    return out;
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

int main() {
  std::ifstream fin("data/6.txt");

  std::vector<std::string> lines;

  for (std::string line; fin >> line;) {
    lines.push_back(line);
  }

  std::vector<double> times(100);

  for (double &time : times) {
    const my::Timer timer;

    Board board(lines);
    StopsMap stops_map(board);

    int y = 0;
    int x = 0;

    for (y = 0; y < board.map_y; ++y) {
      for (x = 0; x < board.map_x; ++x) {
        if (board.at(y, x) == '^') {
          goto L_STOP;
        }
      }
    }
  L_STOP:

    int points = 0;
    int dir = 0;

    while (y > 0 && y < board.map_y - 1 && x > 0 && x < board.map_x - 1) {
      const int new_y = y + dirs[dir].first;
      const int new_x = x + dirs[dir].second;

      if (board.at(new_y, new_x) == '#') {
        dir = (dir + 1) % 4;
      } else {
        if (board.at(new_y, new_x) != ',') {
          stops_map.TestWithObstacle(new_y, new_x, [&]() {
            points += CheckIfInLoop(board, stops_map, y, x, dir);
          });

          board.set(new_y, new_x, ',');
        }
        y = new_y;
        x = new_x;
      }
    }

    if (points != 1705) {
      std::cerr << "cooked : " << points << '\n';
      return EXIT_FAILURE;
    }

    time = timer.ElapsedTime();
  }

  std::cout << std::fixed << std::setprecision(3)
            << std::accumulate(times.begin(), times.end(), 0.0) * 1000 / times.size() << " ms\n";

  return 0;
}

