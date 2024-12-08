#include <cctype>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "utils.hpp"

int main() {
  std::ifstream fin("data/8.txt");

  my::Timer timer;

  std::vector<std::string> lines;

  for (std::string line; std::getline(fin, line);) {
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
          const std::pair<int, int> p1 = {std::get<0>(antennas[i2]) + dy,
                                          std::get<1>(antennas[i2]) + dx};
          if (p1.first >= 0 && p1.first < Y && p1.second >= 0 && p1.second < X &&
              lines[p1.first][p1.second] != '#') {
            lines[p1.first][p1.second] = '#';
            ++points;
          }
        }
        {
          const std::pair<int, int> p1 = {std::get<0>(antennas[i1]) - dy,
                                          std::get<1>(antennas[i1]) - dx};
          if (p1.first >= 0 && p1.first < Y && p1.second >= 0 && p1.second < X &&
              lines[p1.first][p1.second] != '#') {
            lines[p1.first][p1.second] = '#';
            ++points;
          }
        }
      }
    }
  }

  const double elapsed_time = timer.ElapsedTime();

  std::cout << points << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e3 << " ms\n";
}
