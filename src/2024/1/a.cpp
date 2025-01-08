#include <algorithm>
#include <cctype>
#include <cstdint>
#include <sstream>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 1, 'A'>(std::stringstream input_stream) {
  const std::string &input = input_stream.str();
  std::vector<int32_t> list1;
  std::vector<int32_t> list2;

  bool flag = false;
  int32_t num = 0;

  for (const char c : input) {
    if (std::isdigit(c)) {
      num = num * 10 + c - '0';
    } else {
      if (flag) {
        list1.push_back(num);
      } else {
        list2.push_back(num);
      }

      flag = not flag;
      num = 0;
    }
  }
  if (flag) {
    list1.push_back(num);
  } else {
    list2.push_back(num);
  }

  std::ranges::sort(list1);
  std::ranges::sort(list2);

  int64_t dist_sum = 0;

  for (size_t i = 0; i < list1.size(); ++i) {
    dist_sum += std::abs(list1[i] - list2[i]);
  }

  return std::to_string(dist_sum);
}
