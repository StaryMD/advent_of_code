#include <cmath>
#include <cstdlib>
#include <vector>

#include "common.hpp"
#include "solution.hpp"

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
        for (int d = 0; d < nums.size(); ++d) {
          copy = nums;
          copy.erase(copy.begin() + d);

          if (day2_2024::IsSequenceGood(copy)) {
            ++points;
            break;
          }
        }
        nums.clear();
      }
    }
  }

  return std::to_string(points);
}
