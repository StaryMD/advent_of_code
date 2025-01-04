#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "solution.hpp"
#include "utility.hpp"

template <>
std::string Solve<2024, 7, 'B'>(std::stringstream input) {
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

    std::vector<uint64_t> len(nums.size());
    for (size_t i = 0; i < len.size(); ++i) {
      len[i] = my::Pow<uint64_t>(10, std::to_string(nums[i]).size());
    }

    const uint64_t n = my::Pow<uint64_t>(3, nums.size() - 1);
    for (uint64_t i = 0; i < n; ++i) {
      uint64_t sum = nums[0];
      uint64_t pow3 = 1;

      for (size_t j = 1; j < nums.size(); ++j) {
        switch ((i / pow3) % 3) {
          case 0:
            sum += nums[j];
            break;
          case 1:
            sum *= nums[j];
            break;
          case 2:
            sum = sum * len[j] + nums[j];
            break;
        }
        pow3 *= 3;
      }

      if (test_value == sum) {
        points += test_value;
        break;
      }
    }
  }

  return std::to_string(points);
}
