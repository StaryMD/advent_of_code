#include <algorithm>
#include <cstdint>
#include <sstream>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 1, 'A'>(std::stringstream input) {
  std::vector<int32_t> list1;
  std::vector<int32_t> list2;

  for (int32_t a, b; input >> a >> b;) {
    list1.push_back(a);
    list2.push_back(b);
  }

  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  int64_t dist_sum = 0;

  for (size_t i = 0; i < list1.size(); ++i) {
    dist_sum += std::abs(list1[i] - list2[i]);
  }

  return std::to_string(dist_sum);
}
