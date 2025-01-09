#include <cmath>
#include <cstdlib>
#include <vector>

#include "common.hpp"
#include "solution.hpp"

namespace day2b_2024 {

bool IsSequenceGoodWeak(const std::vector<int> &nums) {
  int bad = 0;

  for (int i = 1; i < nums.size(); ++i) {
    const int diff = std::abs(nums[i] - nums[i - 1]);

    bad += diff == 0 || diff > 3;
  }

  return bad < 2;
}

}  // namespace day2b_2024

template <>
std::string Solve<2024, 2, 'B'>(std::stringstream input_stream) {
  int points = 0;
  std::vector<int> nums;
  std::vector<int> copy;

  int num = 0;
  for (const char c : input_stream.str() + '\n') {
    if (std::isdigit(c)) {
      num = num * 10 + c - '0';
    } else {
      nums.push_back(num);
      num = 0;

      if (c == '\n') {
        if (day2b_2024::IsSequenceGoodWeak(nums)) {
          for (int d = 0; d < nums.size(); ++d) {
            copy = nums;
            copy.erase(copy.begin() + d);

            if (day2_2024::IsSequenceGood(copy)) {
              ++points;
              break;
            }
          }
        }

        nums.clear();
      }
    }
  }

  return std::to_string(points);
}
