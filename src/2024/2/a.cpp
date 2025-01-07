#include <cstdint>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 2, 'A'>(std::stringstream input) {
  size_t points = 0;

  for (std::string line; std::getline(input, line);) {
    std::vector<int32_t> nums;
    std::stringstream sline(line);

    for (int a; sline >> a;) {
      nums.push_back(a);
    }

    bool inc = true;
    bool dec = true;
    bool good = true;

    for (int i = 1; i < nums.size(); ++i) {
      const int abs_diff = std::abs(nums[i] - nums[i - 1]);

      if (abs_diff < 1 || abs_diff > 3) {
        good = false;
      }

      if (nums[i] > nums[i - 1]) {
        dec = false;
      }
      if (nums[i] < nums[i - 1]) {
        inc = false;
      }
    }
    if ((inc || dec) && good) {
      ++points;
    }
  }

  return std::to_string(points);
}
