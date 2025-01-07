#include <array>
#include <cstdint>
#include <exception>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "solution.hpp"

namespace day21_2024 {

struct Point {
  int y, x;

  bool operator==(const Point &other) const {
    return y == other.y && x == other.x;
  }
};

const std::unordered_map<char, Point> numpad_coords = {
    {'7', {1, 1}}, {'8', {1, 2}}, {'9', {1, 3}}, {'4', {2, 1}}, {'5', {2, 2}}, {'6', {2, 3}},
    {'1', {3, 1}}, {'2', {3, 2}}, {'3', {3, 3}}, {'0', {4, 2}}, {'A', {4, 3}},
};

const std::array<std::string, 6> numpad = {
    "#####", "#789#", "#456#", "#123#", "##0A#", "#####",
};

const std::unordered_map<char, Point> dirpad_coords = {
    {'^', {0, 1}}, {'A', {0, 2}}, {'<', {1, 0}}, {'v', {1, 1}}, {'>', {1, 2}},
};

constexpr bool IsArrow(const char key) {
  return key == '<' || key == '>' || key == '^' || key == 'v';
}

void DFS(const std::vector<std::pair<Point, char>> &allowed_dirs, std::vector<std::string> &paths,
         const Point &end_coord, const Point coord, const std::string &path) {
  if (numpad[coord.y][coord.x] != '#') {
    if (coord == end_coord) {
      paths.push_back(path);
    } else {
      for (const std::pair<Point, char> &dir : allowed_dirs) {
        const Point new_coord(coord.y + dir.first.y, coord.x + dir.first.x);

        DFS(allowed_dirs, paths, end_coord, new_coord, path + dir.second);
      }
    }
  }
}

std::vector<std::string> GetAllPaths(const char start, const char end) {
  if (start == end) {
    return {"A"};
  }

  if (IsArrow(start) || IsArrow(end)) {
    std::vector<std::string> paths;

    if (start == '<') {
      for (const std::string &path : GetAllPaths('v', end)) {
        paths.push_back('>' + path);
      }
    } else if (end == '<') {
      for (const std::string &path : GetAllPaths(start, 'v')) {
        paths.push_back(path.substr(0, path.size() - 1) + "<A");
      }
    } else {
      const std::array<int, 2> diff = {
          dirpad_coords.at(end).y - dirpad_coords.at(start).y,
          dirpad_coords.at(end).x - dirpad_coords.at(start).x,
      };

      std::string path;

      if (diff[0] < 0) {
        for (int i = 0; i < -diff[0]; ++i) {
          path += '^';
        }
      } else if (diff[0] > 0) {
        for (int i = 0; i < diff[0]; ++i) {
          path += 'v';
        }
      }

      if (diff[1] < 0) {
        for (int i = 0; i < -diff[1]; ++i) {
          path += '<';
        }
      } else if (diff[1] > 0) {
        for (int i = 0; i < diff[1]; ++i) {
          path += '>';
        }
      }

      if (path.size() > 2) {
        std::cout << "fuck\n";
        std::terminate();
      }

      paths.push_back(path + 'A');

      if (path.size() == 2) {
        paths.push_back({path[1], path[0], 'A'});
      }
    }

    return paths;
  }

  const Point start_coord = numpad_coords.at(start);
  const Point end_coord = numpad_coords.at(end);

  const std::array<int, 2> diff = {
      end_coord.y - start_coord.y,
      end_coord.x - start_coord.x,
  };

  std::vector<std::pair<Point, char>> allowed_dirs;

  if (diff[0] > 0) {
    allowed_dirs.push_back({{1, 0}, 'v'});
  } else if (diff[0] < 0) {
    allowed_dirs.push_back({{-1, 0}, '^'});
  }

  if (diff[1] > 0) {
    allowed_dirs.push_back({{0, 1}, '>'});
  } else if (diff[1] < 0) {
    allowed_dirs.push_back({{0, -1}, '<'});
  }

  std::vector<std::string> paths;

  DFS(allowed_dirs, paths, end_coord, start_coord, "");

  for (std::string &path : paths) {
    path += 'A';
  }

  return paths;
}

uint64_t GetCost(std::vector<std::unordered_map<std::string, uint64_t>> &cache,
                 const std::string &code, const int indirections) {
  if (indirections == 0) {
    return code.size();
  }

  uint64_t &cached_value = cache[indirections][code];
  if (cached_value != 0) {
    return cached_value;
  }

  uint64_t total_cost = 0;
  char prev_key = 'A';

  for (const char key : code) {
    uint64_t best_cost = std::numeric_limits<uint64_t>::max();

    for (const std::string &path : GetAllPaths(prev_key, key)) {
      best_cost = std::min(best_cost, GetCost(cache, path, indirections - 1));
    }

    prev_key = key;
    total_cost += best_cost;
  }

  cached_value = total_cost;

  return total_cost;
}

uint64_t SolveHelper(std::stringstream &input, const int indirections) {
  uint64_t points = 0;

  for (std::string code; std::getline(input, code);) {
    std::vector<std::unordered_map<std::string, uint64_t>> cache(indirections + 1);

    points += std::stoi(code.substr(0, 3)) * GetCost(cache, code, indirections);
  }

  return points;
}

}  // namespace day21_2024

template <>
std::string Solve<2024, 21, 'A'>(std::stringstream input) {
  return std::to_string(day21_2024::SolveHelper(input, 3));
}

template <>
std::string Solve<2024, 21, 'B'>(std::stringstream input) {
  return std::to_string(day21_2024::SolveHelper(input, 26));
}
