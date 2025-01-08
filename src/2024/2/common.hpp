#pragma once

#include <cstdlib>
#include <vector>

namespace day2_2024 {

inline bool IsSequenceGood(const std::vector<int> &nums) {
  bool inc = true;
  bool dec = true;
  bool good = true;

  for (int i = 1; i < nums.size() && (inc || dec) && good; ++i) {
    const int abs_diff = std::abs(nums[i] - nums[i - 1]);

    good &= abs_diff == 1 || abs_diff == 2 || abs_diff == 3;
    dec &= nums[i] > nums[i - 1];
    inc &= nums[i] < nums[i - 1];
  }

  return (inc || dec) && good;
}

}  // namespace day2_2024
