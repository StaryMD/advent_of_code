#include <cctype>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 8, 'B'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  const int Y = lines.size();
  const int X = lines[0].size();

  std::vector<std::tuple<int, int, char>> antennas;

  for (size_t y = 0; y < lines.size(); ++y) {
    for (size_t x = 0; x < lines[0].size(); ++x) {
      if (std::isalnum(lines[y][x])) {
        antennas.push_back({y, x, lines[y][x]});
      }
    }
  }

  int points = 0;

  for (int i1 = 0; i1 < antennas.size() - 1; ++i1) {
    for (int i2 = i1 + 1; i2 < antennas.size(); ++i2) {
      if (std::get<2>(antennas[i1]) == std::get<2>(antennas[i2])) {
        const int dy = std::get<0>(antennas[i2]) - std::get<0>(antennas[i1]);
        const int dx = std::get<1>(antennas[i2]) - std::get<1>(antennas[i1]);

        {
          std::pair<int, int> p1 = {std::get<0>(antennas[i2]), std::get<1>(antennas[i2])};
          while (p1.first >= 0 && p1.first < Y && p1.second >= 0 && p1.second < X) {
            if (lines[p1.first][p1.second] != '#') {
              lines[p1.first][p1.second] = '#';
              ++points;
            }

            p1.first += dy;
            p1.second += dx;
          }
        }
        {
          std::pair<int, int> p1 = {std::get<0>(antennas[i1]), std::get<1>(antennas[i1])};
          while (p1.first >= 0 && p1.first < Y && p1.second >= 0 && p1.second < X) {
            if (lines[p1.first][p1.second] != '#') {
              lines[p1.first][p1.second] = '#';
              ++points;
            }

            p1.first -= dy;
            p1.second -= dx;
          }
        }
      }
    }
  }

  return std::to_string(points);
}
