#include <cstdint>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 7, 'A'>(std::stringstream input) {
  uint64_t points = 0;

  for (std::string line; std::getline(input, line);) {
    std::stringstream sline(line);

    uint64_t test_value;
    char temp;
    std::vector<uint64_t> nums;
    sline >> test_value;
    sline >> temp;
    for (uint64_t a; sline >> a;) {
      nums.push_back(a);
    }

    const uint64_t n = (1 << (nums.size() - 1));

    for (uint64_t i = 0; i < n; ++i) {
      uint64_t sum = nums[0];

      for (size_t j = 1; j < nums.size(); ++j) {
        if (i & (1 << (j - 1))) {
          sum += nums[j];
        } else {
          sum *= nums[j];
        }
      }

      if (test_value == sum) {
        points += test_value;
        break;
      }
    }
  }

  return std::to_string(points);
}
