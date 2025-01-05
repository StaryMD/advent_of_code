#include <cstdint>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day11 {

constexpr uint32_t kSize = 140;

struct Point {
  const uint32_t x;
  const uint32_t y;

  Point(const uint32_t x_, const uint32_t y_) : x(x_), y(y_) {}
};

std::vector<Point> GetGalaxies(std::stringstream &input) {
  std::vector<Point> galaxies;

  galaxies.reserve(kSize * kSize);

  for (uint32_t i = 0; const char ch : input.str()) {
    switch (ch) {
      case '#': {
        galaxies.emplace_back(i % kSize + 1, i / kSize + 1);
      }
      case '.': {
        ++i;
        break;
      }
    }
  }

  return galaxies;
}

std::vector<int32_t> CalculateDistances(const std::vector<Point> &galaxies,
                                        const int expansion_rate) {
  std::vector<int32_t> distances((kSize + 1) * 2);

  int32_t* const dist_hor = distances.data();
  int32_t* const dist_ver = distances.data() + kSize + 1;

  for (int64_t x = 1; x <= kSize; ++x) {
    bool is_empty = true;

    for (const Point galaxy : galaxies) {
      if (galaxy.x == x) {
        is_empty = false;
      }
    }
    dist_hor[x] = dist_hor[x - 1] + 1 + is_empty * (expansion_rate - 1);
  }

  for (int64_t y = 1; y <= kSize; ++y) {
    bool is_empty = true;

    for (const Point galaxy : galaxies) {
      if (galaxy.y == y) {
        is_empty = false;
      }
    }

    dist_ver[y] = dist_ver[y - 1] + 1 + is_empty * (expansion_rate - 1);
  }

  return distances;
}

uint64_t CalculateAnswer(const std::vector<Point> &galaxies,
                         const std::vector<int32_t> &distances) {
  uint64_t sum = 0;

  const int32_t* const dist_hor = distances.data();
  const int32_t* const dist_ver = distances.data() + kSize + 1;

  for (uint32_t i = 0; i < static_cast<uint32_t>(galaxies.size()) - 1; ++i) {
    for (uint32_t j = i + 1; j < static_cast<uint32_t>(galaxies.size()); ++j) {
      sum += std::abs(dist_hor[galaxies[j].x] - dist_hor[galaxies[i].x]) +
             (dist_ver[galaxies[j].y] - dist_ver[galaxies[i].y]);
    }
  }

  return sum;
}

std::string SolveHelper(std::stringstream &input, const int expansion_rate) {
  const std::vector<Point> galaxies = GetGalaxies(input);
  const std::vector<int32_t> distances = CalculateDistances(galaxies, expansion_rate);
  const uint64_t answer = CalculateAnswer(galaxies, distances);

  return std::to_string(answer);
}

}  // namespace day11

template <>
std::string Solve<2023, 11, 'A'>(std::stringstream input) {
  return day11::SolveHelper(input, 2);
}

template <>
std::string Solve<2023, 11, 'B'>(std::stringstream input) {
  return day11::SolveHelper(input, 1000000);
}
