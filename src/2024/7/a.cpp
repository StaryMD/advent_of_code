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

    std::vector<uint64_t> nums;

    uint64_t test_value;
    char temp;
    sline >> test_value;
    sline >> temp;
    for (uint64_t a; sline >> a;) {
      nums.push_back(a);
    }

    struct State {
      uint64_t curr;
      int index;
    };

    std::vector<State> states;
    states.emplace_back(nums[0], 1);

    while (not states.empty()) {
      const auto [curr, index] = states.back();
      states.pop_back();

      if (index == nums.size()) {
        if (curr == test_value) {
          points += test_value;
          break;
        }
        continue;
      }

      if (curr > test_value) {
        continue;
      }

      if (curr + nums[index]) {
        states.emplace_back(curr + nums[index], index + 1);
      }
      if (curr * nums[index]) {
        states.emplace_back(curr * nums[index], index + 1);
      }
    }
  }

  return std::to_string(points);
}
