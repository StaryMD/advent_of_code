#pragma once

#include <cstdlib>
#include <vector>

namespace day2_2024 {

inline bool IsSequenceGood(const std::vector<int> &nums) {
  bool inc = true;
  bool dec = true;
  bool good = true;

  for (int i = 1; i < nums.size() && (inc || dec) && good; ++i) {
    const int diff = nums[i] - nums[i - 1];

    good &= std::abs(diff) < 4;
    dec &= diff > 0;
    inc &= diff < 0;
  }

  return (inc || dec) && good;
}

}  // namespace day2_2024
