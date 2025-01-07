#include <cmath>
#include <cstdlib>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 2, 'B'>(std::stringstream input) {
  int points = 0;

  for (std::string line; std::getline(input, line);) {
    std::vector<int> nums;
    std::stringstream sline(line);

    for (int a; sline >> a;) {
      nums.push_back(a);
    }

    for (int d = 0; d < nums.size(); ++d) {
      bool inc = true;
      bool dec = true;
      bool good = true;

      std::vector<int> copy = nums;
      copy.erase(copy.cbegin() + d);

      for (int i = 1; i < copy.size(); ++i) {
        const int abs_diff = std::abs(copy[i] - copy[i - 1]);

        if (abs_diff < 1 or abs_diff > 3) {
          good = false;
        }
        if (copy[i] > copy[i - 1]) {
          dec = false;
        }
        if (copy[i] < copy[i - 1]) {
          inc = false;
        }
      }
      if ((inc or dec) and good) {
        ++points;
        break;
      }
    }
  }

  return std::to_string(points);
}
