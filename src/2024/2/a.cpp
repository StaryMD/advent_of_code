#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "common.hpp"
#include "solution.hpp"

template <>
std::string Solve<2024, 2, 'A'>(std::stringstream input_stream) {
  int points = 0;
  std::vector<int> nums;

  int num = 0;
  for (const char c : input_stream.str() + '\n') {
    if (std::isdigit(c)) {
      num = num * 10 + c - '0';
    } else {
      nums.push_back(num);
      num = 0;

      if (c == '\n') {
        if (day2_2024::IsSequenceGood(nums)) {
          ++points;
        }

        nums.clear();
      }
    }
  }

  return std::to_string(points);
}
