#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 1, 'B'>(std::stringstream input) {
  std::vector<int32_t> list1;
  std::array<int32_t, 100'000> freq;
  std::fill(freq.begin(), freq.end(), 0);

  for (int32_t a, b; input >> a >> b;) {
    list1.push_back(a);

    ++freq[b];
  }

  int64_t similarity = 0;

  for (const int32_t item : list1) {
    similarity += item * freq.at(item);
  }

  return std::to_string(similarity);
}
