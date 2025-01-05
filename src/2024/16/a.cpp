#include <climits>
#include <cstdio>
#include <string>
#include <vector>

#include "common.hpp"
#include "solution.hpp"

template <>
std::string Solve<2024, 16, 'A'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  day16::Map map(lines);

  const auto [start_y, start_x] = FindCell(map, 'S');

  GetTrailScore(map, start_y, start_x, 1, 0);

  const auto [end_y, end_x] = FindCell(map, 'E');

  return std::to_string(map.visited(end_y, end_x));
}
